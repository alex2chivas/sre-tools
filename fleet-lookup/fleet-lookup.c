/*
 * fleet-lookup.c
 * Parses a space-delimited device inventory file and provides
 * case-insensitive search by CHID.
 *
 * Usage: ./fleet-lookup <filename>
 * Compile: gcc -o fleet-lookup fleet-lookup.c
 *        
*/
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<strings.h>
#define MAX_INPUT 1024

struct device {
	int mjid;
	char chid[16];
	char ip[16];
};

int device_count(const char *filename) {
	FILE *fp = fopen(filename, "r");
	char line[MAX_INPUT];
	int count = 0;

	while (fgets(line, MAX_INPUT, fp) != NULL) {
		count++;	
	}
	fclose(fp);
	return count;
}

void data_parse(const char *filename, struct device *fleet, int count) {
	FILE *fp = fopen(filename, "r");
	char line[MAX_INPUT];
	fgets(line, MAX_INPUT, fp);	
	int i = 0;

	while (fgets(line, MAX_INPUT, fp) != NULL && i < count) {
		char *field = strtok(line, " ");
		if (field == NULL) {i++; continue;}
		fleet[i].mjid = atoi(field);

		field = strtok(NULL, " ");
		if (field == NULL) {i++; continue;}
		strcpy(fleet[i].chid, field);

		field = strtok(NULL, " ");
		if (field == NULL) {i++; continue;}
		strcpy(fleet[i].ip, field);

		i++;
	
	}

	fclose(fp);

}

void search_device(struct device *fleet, int count) {
	char chid[16];
	getchar();
	printf("Enter CHID: ");
	fgets(chid, 16, stdin);
	chid[strcspn(chid, "\n")] = '\0';

	int chid_len = strlen(chid);

	if (chid_len == 0) {
		printf("No CHID entered\n");
		return;
	}


	for (int i = 0; i < count; i++) {
		if (strcasecmp(fleet[i].chid, chid) == 0) {
			printf("MJID: %d  CHID: %s  IP: %s\n", fleet[i].mjid, fleet[i].chid, fleet[i].ip);
			return;
		}
	}

	printf("CHID %s not found\n", chid);
}

int main(int argc, char *argv[]) {
	if(argc < 2) {
		printf("Usage: %s <filename>\n", argv[0]);
		return 1;
	}

	const char *filename = argv[1];
	int count = device_count(filename) - 1;


	struct device *fleet = malloc(sizeof(struct device) * count);

	data_parse(filename, fleet, count);

	for (int i = 0; i < count; i++) {
		printf("MJID: %d  CHID: %s  IP: %s\n", fleet[i].mjid, fleet[i].chid, fleet[i].ip);
	}


	char selection;
	printf("Want to search for CHID? (y or n): ");
	scanf(" %c", &selection);

	if (selection == 'y' || selection == 'Y') {	
		search_device(fleet, count);
	} 

	free(fleet);
	return 0;
		

}
