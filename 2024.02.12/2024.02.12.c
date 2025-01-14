#include <stdio.h>
#include <stdlib.h>

char** getString() {
	char **strr = (char**) malloc (3 * sizeof(char*));
	for (int i = 0; i < 3; i++) {
		strr[i] = (char*) malloc (20 * sizeof(char));
		printf("Enter string %d: ", i);
		scanf(" %[^\n]", strr[i]);
	}
	return strr;
}

int main() {
	char **strr = getString();
	for (int i = 0; i < 3; i++) {
		printf("%s\n", strr[i]);
	}
	
	for (int i = 0; i < 3; i++) {
		free(*(strr + i));
	}
	free(strr);
	
	return 0;
}