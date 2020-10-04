#include "Client.h"
#include <string>

unsigned const int IP_STR_MAX_SIZE = 16;
unsigned const int PORT = 2008;

void main() {
	char* ip;
	ip = (char*)malloc(IP_STR_MAX_SIZE);

	printf("ip> ");
	gets_s(ip, IP_STR_MAX_SIZE);

	Client* client = new Client(ip, PORT);

	client->sendRequest();
	client->close();

	system("pause");
	free(ip);
}