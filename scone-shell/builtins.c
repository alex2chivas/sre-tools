#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "builtins.h"

int run_cd(char *path) {
	if (path == NULL) {
		printf("Usage: cd <directory>\n");
		return 1;
	}

	if(chdir(path) != 0) {
		printf("Directory not found: %s\n", path);
		return 1;
	}

	return 0;
}

int is_exit(char *cmd) {
	return strcmp(cmd, "exit") == 0;
}
