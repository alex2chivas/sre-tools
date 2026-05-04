/*
 * mini-nc.c
 * A minimal TCP client similar to netcat. Connects to a host
 * and port, then provides an interactive session for sending
 * and receiving raw TCP data.
 *
 * Compile: gcc -o mini-nc mini-nc.c
 * Usage: ./mini-nc <ip> <port>
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>          // close()
#include <arpa/inet.h>       // socket structs and functions


int create_socket() {
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) {
		printf("Socket creation failed\n");
		return -1;
	}

	printf("Socket created\n");
	return sock;
}

int main(int argc, char *argv[]) {
	char input[256];
	char buffer[4096];
	int sock = create_socket();
	if (sock < 0) return 1;

	struct sockaddr_in server;
	server.sin_family = AF_INET; // IPv4
	server.sin_port = htons(atoi(argv[2])); // convert port to network byte order
	server.sin_addr.s_addr = inet_addr(argv[1]); // convert IP string to netwrok format

	if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0) {
		printf("Connection failed\n");
		close(sock);
		return 1;
	}

	printf("Connected to %s:%s\n", argv[1], argv[2]);
	int bytes;
	while (1) {
		printf("> ");
		fgets(input, 256, stdin);

		send(sock, input, strlen(input), 0);

		bytes = recv(sock, buffer, 4096, 0);
		if (bytes <= 0) {
			printf("Connection closed\n");
			break;
		}
		buffer[bytes] = '\0';
		printf("%s", buffer);
	
	}

	close(sock);
	return 0;
}
