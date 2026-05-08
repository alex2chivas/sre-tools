#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>
#include"signal_handler.h"

extern char cwd[256];

void handle_signal(int sig) {
	switch (sig) {
		case SIGINT:
			getcwd(cwd, 256); //refresh prompt after cd
			printf("\n%s scone-shell> ", cwd);
			fflush(stdout);
			break;
		case SIGTERM:
			printf("Shutting down...\n");
			exit(0);
			break;
	}
}
