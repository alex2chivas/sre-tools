/*
 * log-parser.c
 * A CLI log parsing tool that searches log files for keywords,
 * similar to grep. Supports case-sensitive and case-insensitive
 * search with match count summary.
 *
 * Compile: gcc -o log-parser log-parser.c
 * Usage: ./log-parser <file> -s <keyword> [-i]
*/

#define _GNU_SOURCE
#include<stdio.h>     // → printf, fopen, fgets, fclose
#include<stdlib.h>     //→ exit
#include<string.h>     //→ strcmp, strstr, strcasestr

void line_match(char *filepath, char *keyword, int case_insensitive) {
	FILE *fp = fopen(filepath, "r");
	char line[1024];
	int matches = 0;

	while(fgets(line, 1024, fp) != NULL) {
		if (case_insensitive == 1) {
			if (strcasestr(line, keyword) != NULL) {
				printf("%s", line);
				matches++;
			}
		} else if (strstr(line, keyword) != NULL) {
			printf("%s", line);
			matches++;
		}

	}	

	printf("\n--- %d matches found ---\n", matches);

}


int check_file_exist(char *filename) {	
	FILE *fp = fopen(filename, "r");

	if (fp == NULL) {
		printf("File does not exist: %s\n", filename);
		return 1;
	}

	fclose(fp);
	return 0;
}

void usage(char *program) {
	printf("Usage: %s <file> -s <keyword> [-i]\n\n", program);
	printf("Options:\n");
	printf("  -s <keyword>   Search for keyword in log file\n");
	printf("  -i             Case insensitive search (optional)\n\n");
	printf("Examples:\n");
	printf("  %s /var/log/syslog -s \"warning\"\n", program);
	printf("  %s /var/log/syslog -s \"error\" -i\n", program);
	printf("\nNotes:\n");
	printf("  Might need to run application as sudo to read the logs.\n");
}

int main(int argc, char *argv[]) {
	int case_insensitive = 0;

	if ( argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
		usage(argv[0]);
		return 0;
	}

	if (argc < 4 || argc > 5) {
		usage(argv[0]);
		return 1;
	}

	int file_exist = check_file_exist(argv[1]);

	if (file_exist == 1) {
		usage(argv[0]);
		return 1;
	
	
	}

	if (argc == 5 && strcmp(argv[4], "-i") == 0) {
		case_insensitive = 1;
	}

	if (strcmp(argv[2], "-s") == 0) {
		line_match(argv[1], argv[3], case_insensitive);
	}

	return 0;
}
