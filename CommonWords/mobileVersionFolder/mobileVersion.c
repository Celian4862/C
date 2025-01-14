// There is no executable in the folder because this code may not run correctly

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef MAX_CHAR
#define MAX_CHAR 100
#endif

void getSentences(char*, char*);
void string_tolower(char*, int);
void remove_special(char*, int);
char** find_common_words(char*, char*, int*);
void printWords(char**, int);

int main() {
	system("cls");
	// Dynamically allocated so that memory can be resized if needed
	char sentence1 = (char) malloc (MAX_CHAR), sentence2 = (char) malloc (MAX_CHAR);

	// Get the sentences necessary for the task
	getSentences(sentence1, sentence2);
	// To make typing shorter, create variables to store the string lengths of the sentences.
	int size1 = strlen(sentence1), size2 = strlen(sentence2);
	// Have a word count variable for later.
	int word_count = 0;

	// Make both strings lowercase to deal with them easier.
	string_tolower(sentence1, size1);
	string_tolower(sentence2, size2);

	// Remove special characters from both strings
	remove_special(sentence1, size1);
	remove_special(sentence2, size2);

	// Dynamically allocated by the function.
	char **words = find_common_words(sentence1, sentence2, &word_count);

	printWords(words, word_count);

	free(sentence1);
	free(sentence2);
	free(*words);
	free(words);

	return 0;
}

// Function is special: it has to receive dynamically allocated strings, or else an error may occur.
void getSentences(char *sentence1, char *sentence2) {
	printf("Enter a sentence (max 100 characters): ");
	scanf(" %[^\n]", sentence1);
	sentence1 = (char*) realloc(sentence1, strlen(sentence1));

	printf("Enter another sentence (max 100 characters): ");
	scanf(" %[^\n]", sentence2);
	sentence2 = (char*) realloc(sentence2, strlen(sentence2));
}

int compareSTRLEN(char *s1, char *s2) {
	if (strlen(s1) < strlen(s2)) {
		return strlen(s1);
	} else {
		return strlen(s2);
	}
}

void string_tolower(char *s, int size) {
	for (int i = 0; i < size; i++) {
		s[i] = tolower(s[i]);
	}
}

void remove_special(char *s, int size) {
	for (int i = 0; i < size; i++) {
		if (iscntrl(s[i]) && s[i] != '\0' || ispunct(s[i])) {
			s[i] = ' ';
		}
	}
}

char** find_common_words(char *s1, char *s2, int *word_count) {
	// Initialise the tokens.
	char *token1 = strtok(s1, " "), *token2 = strtok(s2, " ");
	// Initialise the array of words.
	char *words = (char*) malloc (sizeof(char*));
	words = (char) malloc (compareSTRLEN(s1, s2));
	// Initialise variables for loop conditions.
	int i = 0;
	while (token1) {
		if (!strcmp(token1, token2)) {
			strcpy(words[i++], token1);
			words = (char**) realloc (words, sizeof(char**) + (i + 1));
		}
		token1 = strtok(NULL, " ");
		token2 = strtok(NULL, " ");
	}
	*word_count = i;
	return words;
}

void printWords(char **s, int word_count) {
	for (int i = 0; i < word_count; i++) {
		printf("%s\n", s[i]);
	}
}