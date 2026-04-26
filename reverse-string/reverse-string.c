/*
 * reverse-string.c
 * Takes user input and prints the string reversed.
 *
 * Compile: gcc -o reverse-string reverse-string.c
 * Usage: ./reverse-string
*/

#include<stdio.h>
#include<string.h>
#define MAX_INPUT 256

int main() {
	char input[MAX_INPUT]; 
	printf("Please enter text: ");
	fgets(input, MAX_INPUT, stdin);
	input[strcspn(input, "\n")] = '\0';

	int len = strlen(input);
	char new_input[len + 1];
	int new_len = len - 1;

	for (int i = 0; i < len; i++) {
		new_input[i] = input[new_len];
		new_len--;
	}

	new_input[len] = '\0';

	printf("%s\n", new_input);	

	return 0;
}
