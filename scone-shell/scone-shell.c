/*
 * scone-shell.c
 * A minimal Unix shell written in C. Supports external commands
 * with arguments, built-in cd and exit, working directory display,
 * and error handling for invalid commands.
 *
 * Compile: gcc -o scone-shell scone-shell.c
 * Usage: ./scone-shell
*/

#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
#include<signal.h>
#include"signal_handler.h"
#include"builtins.h"
#include"executor.h"

char cwd[256]; // used inside the signal_handler


int main() {
	char input[256];

	signal(SIGINT, handle_signal);
	signal(SIGTERM, handle_signal);

	while(1) {
		getcwd(cwd, 256); // refresh prompt after cd
		printf("%s scone-shell> ", cwd);
		fgets(input, 256, stdin);
		input[strcspn(input, "\n")] = '\0';


		if (input[0] == '\0') {
			continue;
		}

		char *args[64];
		int i = 0;

		char *token = strtok(input, " ");

		while (token != NULL) {
			args[i] = token;
			i++;
			token = strtok(NULL, " "); 
		}
		args[i] = NULL; // exec requires NULL-terminated array

		if (is_exit(args[0])) {
			break; // leaves the while loop
		}
		if (strcmp(args[0], "cd") ==0) {
			run_cd(args[1]);
			continue;
		}

		run_command(args);

	}

	return 0;
}
