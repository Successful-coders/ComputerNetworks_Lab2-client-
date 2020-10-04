#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include "Client.h"
#include "stdio.h"

Client::Client(const char* ip, unsigned short port) {

	this->ip = ip;
	this->port = port;

	int res = WSAStartup(0x0101, &wsaData);
	if (res == SOCKET_ERROR) {
		printf("WSAStartuo() failed: %ld\n", GetLastError());
	}

	// Получаем дескриптор сокета клиента.
	clientSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (clientSocket == SOCKET_ERROR) {
		printf("Failed to create server socket: %ld\n", GetLastError());
	}

	// Заполняем информацю о сокете клиента.
	serverSIN.sin_family = AF_INET;
	serverSIN.sin_port = htons(port);
	serverSIN.sin_addr.S_un.S_addr = inet_addr(ip);

	buf = (char*)malloc(BUF_SIZE);
}

Client::~Client() {
	free(buf);
}

// Отправляем запрос серверу.
void Client::sendRequest() {

	// Подключаемся к серверу.
	int res = connect(clientSocket, (LPSOCKADDR)&serverSIN, sizeof(serverSIN));
	if (res == SOCKET_ERROR) {
		printf("Connection failed: %ld\n", GetLastError());
		return;
	}
	printf("Connection made successfully.\n");

	printf("Enter two numbers: ");
	gets_s(buf, BUF_SIZE);

	// Отправляем серверу числа.
	res = send(clientSocket, buf, strlen(buf), 0);
	if (res == SOCKET_ERROR) {
		printf("Failed to send data: %ld\n", GetLastError());
		return;
	}

	for (int i = 0; buf[i] != '\0'; i++) {
		buf[i] = '\0';
	}

	// Получаем сумму чисел.
	res = recv(clientSocket, buf, BUF_SIZE, 0);
	if (res == SOCKET_ERROR) {
		printf("Server is not responding: %ld\n", GetLastError());
	}

	printf("Sum: %s\n", buf);
}

void Client::close() {
	closesocket(clientSocket);
	WSACleanup();
	printf("Client closed.\n");
}