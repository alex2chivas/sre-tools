/*
 * port-scanner.c
 * A multi-threaded TCP port scanner. Scans a range of ports on a target IP
 * by spawning one thread per port and attempting a TCP connect to each.
 * Ports that accept the connection are reported as OPEN.
 *
 * Compile: gcc -o port-scanner port-scanner.c -lpthread
 * Usage: ./port-scanner <ip> <start_port> <end_port>
*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#include<unistd.h>
#include<arpa/inet.h>

struct scan_data {
	char ip[16];
	int port;
};

void *scan_port(void *arg) {
	struct scan_data *data = (struct scan_data *)arg;

	// create socket
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0) return NULL;

	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(data->port);
	server.sin_addr.s_addr = inet_addr(data->ip);

	// try to connect
	if(connect(sock, (struct sockaddr *)&server, sizeof(server)) == 0) {
		printf("Port %d is OPEN\n", data->port);
	}	

	close(sock);
	return NULL;

}

int main(int argc, char *argv[]) {
	char *ip = argv[1];
	int start_port = atoi(argv[2]);
	int end_port = atoi(argv[3]);

	int num_ports = end_port - start_port + 1;
	pthread_t threads[num_ports];
	struct scan_data data[num_ports]; // array of structs

	int idx = 0;
	for (int p = start_port; p <= end_port; p++) {
		strcpy(data[idx].ip, ip);
		data[idx].port = p;
		pthread_create(&threads[idx], NULL, scan_port, &data[idx]);		
		idx++;
	}

	for (int i = 0; i < num_ports; i++) {
		pthread_join(threads[i], NULL);
	}

	return 0;
}
