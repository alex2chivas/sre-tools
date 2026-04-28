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

int main() {
	char input[256];
	char cwd[256];

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

		if (strcmp(args[0], "exit") == 0) {
			break;
		}

		if (strcmp(args[0], "cd") == 0) {
			if (args[1] == NULL) {
				printf("Usage: cd <directory>\n");
			} else {
				if (chdir(args[1]) != 0) {
					printf("Directory not found: %s\n", args[1]); 
				}
			}
			continue; // Skip fork/exec for builtins
		}


		pid_t pid = fork();
		if (pid == 0) {
			execvp(args[0], args);  // Will replace child process with command. If something returns will go down to printf
						// and exit();  
			printf("Command not found: %s\n", args[0]);
			exit(1); // kill child so it doesn't become a second shell

		} else {
			wait(NULL);
		}


	}

	return 0;
}
