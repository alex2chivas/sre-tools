#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include "executor.h"

void run_command(char *args[]) {
	pid_t pid = fork();

	if (pid ==0) {
		execvp(args[0], args);
		printf("Command not found %s\n", args[0]);
		exit(1);
	} else {
		wait(NULL);
	}
}
