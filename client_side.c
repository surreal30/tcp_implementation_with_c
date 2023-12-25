#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main()
{
	char *ip = "127.0.0.1";
	int port = 5566;

	int sock;
	struct sockaddr_in addr;
	char buffer[1024];

	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock < 0)
	{
		perror("[-]Socket Error");
		exit(1);
	}
	printf("[+]TCP server socket created. \n");

	memset(&addr, '\0', sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port = port;
	addr.sin_addr.s_addr = inet_addr(ip);

	connect(sock, (struct sockaddr*)&addr, sizeof(addr));
	printf("Connected to server. \n");

	bzero(buffer, 1024);
	strcpy(buffer, "Hello, this is client!");
	printf("client: %s \n", buffer);
	send(sock, buffer, strlen(buffer), 0);

	bzero(buffer, 1024);
	recv(sock, buffer, sizeof(buffer), 0);
	printf("Server: %s \n", buffer);

	close(sock);
	printf("Disconnected from the server. \n");

	return 0;
}