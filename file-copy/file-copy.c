/*
 * file-copy.c
 * A simple file copy tool similar to the cp command.
 * Checks if the source file exists, warns before overwriting
 * an existing destination file, and copies line by line.
 *
 * Compile: gcc -o file-copy file-copy.c
 * Usage: ./file-copy <source> <destination>
 *        ./file-copy -h | --help
*/

#include<string.h>
#include<stdio.h>
#include<stdlib.h>

void usage(char *program_name) {
	printf("Usage: %s  <source> <destination>\n", program_name);
	printf("Copies source file to destination.\n");
}

int check_source_file(char *filename) {
	FILE *fp = fopen(filename, "r");
	if (fp == NULL) {
		printf("File not found: %s\n", filename);
		return 1;
	}
	fclose(fp);
	return 0;
}

int check_destination_file(char *filename) {
	FILE *fp = fopen(filename, "r");

	if (fp != NULL) {
		fclose(fp);
		char answer;
		printf("You sure you want to over-ride the file?(y or n): ");
		scanf(" %c", &answer);
		if (answer == 'y' || answer == 'Y') {
			printf("Over-riding file....\n");
			return 0;
		}

		printf("Exiting...\n");
		return 1;
	}

	return 0;
}

void copy_to_destination(char *source, char *destination) {
	FILE *src = fopen(source, "r");
	FILE *dst = fopen(destination, "w");
	char line[1024];

	while (fgets(line, 1024, src) != NULL ) {
		fprintf(dst, "%s", line);
	}
	
	printf("Copy done: %s\n", destination);
	fclose(src);
	fclose(dst);
}

int main(int argc, char *argv[] ) {
	if (argc == 2 && (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)) {
		usage(argv[0]);
		return 0;
	}

	if (argc != 3) {
		usage(argv[0]);
		return 1;
	}
	
	int source_file_exist = check_source_file(argv[1]);

	if (source_file_exist == 1) {
		exit(1);
	}

	int destination_file_exist = check_destination_file(argv[2]);


	if (destination_file_exist == 1) {
		exit(1);
	}

	copy_to_destination(argv[1], argv[2]);

	return 0;	
}
