#include <stdio.h>      // printf
#include <stdlib.h>     // exit
#include <string.h>     // strchr, strtok
#include <unistd.h>     // fork, execvp, dup2, close, pipe, STDIN_FILENO, STDOUT_FILENO
#include <sys/wait.h>   // wait
#include "pipe_executor.h"

void run_piped_command(char *input) {
	char *cmd1_str = strtok(input, "|"); // eg: ls -la
	char *cmd2_str = strtok(NULL, "|"); // eg: grep -vi

	// Now parse each side into its own array
	char *args1[64];
	char *args2[64];	

	int i = 0;
	char *token = strtok(cmd1_str, " ");
	while (token != NULL) {
		args1[i++] = token;
		token = strtok(NULL, " ");
	}
	args1[i] = NULL;

	i = 0;
	token = strtok(cmd2_str, " ");
	while (token != NULL) {
		args2[i++] = token;
		token = strtok(NULL, " ");
	}
	args2[i] = NULL;

	// Create pipe
	int fds[2];
	pipe(fds);

	// First fork - cmd1
	pid_t pid1 = fork();
	
	if (pid1 == 0) {
		dup2(fds[1], STDOUT_FILENO);
		close(fds[0]);
		close(fds[1]);
		execvp(args1[0], args1);
		exit(1);
	}	

       pid_t pid2 = fork();
       if (pid2 == 0) {
       		dup2(fds[0], STDIN_FILENO);
		close(fds[1]);
		close(fds[0]);
		execvp(args2[0], args2);
		exit(1);
       }

       close(fds[0]);
       close(fds[1]);
       wait(NULL);
       wait(NULL);

}
