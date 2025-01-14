#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifndef MAX
#define MAX 100
#endif

/* For some reason, this isn't working on gcc, but it works on other compilers such as OnlineGDB. */

int main() {
    // Variable declarations
    // s1 and s2 for storing the sentences
	char *s1 = (char*) malloc (MAX + 1), *s2 = (char*) malloc (MAX + 1);
    // words for storing the common words
    char **words;
    // saveptr1 and saveptr2 for storing pointers to the next null character in the given strings; it's for strtok_r
    char *saveptr1, *saveptr2;
    // Pointers to the words in the given strings
    char *token1, *token2;
    // Stores the original, unmodified string (meaning no null characters between words) for restarting the inner loop
    char *s2_copy;

    // Sentence input
	printf("Enter a sentence (max 100 characters): ");
	scanf(" %[^\n]", s1);
	printf("Enter another sentence (max 100 characters): ");
	scanf(" %[^\n]", s2);

    // Initialising integers
    // Size of both strings; especially useful in reallocating memory
	int size1 = strlen(s1), size2 = strlen(s2);
    // Word count to limit the for loop that prints the common words
    int word_count = 0;
    // Finds which string size is shorter so that the 2D array "words" takes up the least amount of memory (taking into account the assumption that the common word could easily be the entirety of one or both of the strings).
    int shorter = (size1 < size2) ? size1 : size2;
    // Iterating variable.
    int i;

    // Resizing memory to waste less storage
    s1 = (char*) realloc(s1, strlen(s1) + 1);
    s2 = (char*) realloc(s2, strlen(s2) + 1);

    // Initialise the first token; to be used in the outer loop
    token1 = strtok_r(s1, " ", &saveptr1);
    // Give exactly sufficient memory to the copy of s2
    s2_copy = (char*) malloc (strlen(s2) + 1);

    // Turning the words lowercase and replacing all special characters (including control characters) with a space
    for (i = 0; i < size1; i++) {
		s1[i] = tolower(s1[i]);
        if (iscntrl(s1[i]) && s1[i] != '\0' || ispunct(s1[i])) {
			s1[i] = ' ';
		}
	}
    for (i = 0; i < size2; i++) {
        s2[i] = tolower(s2[i]);
        if (iscntrl(s2[i]) && s2[i] != '\0' || ispunct(s2[i])) {
			s2[i] = ' ';
		}
    }

    // Identifying words
    /* My style is to compare words as they come. Another valid style (and actually much simpler style) is to store all the words (preferably in an array of structs that contain strings) and then compare them in a for loop instead of a while loop with strtok_r(). */
    // Storing s2's value in s2_copy
    strcpy(s2_copy, s2);
    while (token1) {
        // Refreshing the string s2 so that token2's loop can work properly
        strcpy(s2, s2_copy);
        // Assigning token2 with the first word in s2
        token2 = strtok_r(s2, " ", &saveptr2);
        // Begin inner loop to compare one s1 word with all the words in s2
        while (token2) {
            // If the words are the same:
            if (!strcmp(token1, token2)) {
                // Giving words enough space to accomodate the new word
                words = (char**) realloc (words, sizeof(char*) * ((word_count) + 1));
                // Give the next index maximum space for the longest possible word in the shorter string.
                words[word_count] = (char*) malloc (shorter);
                // Copy token1 to the first available index of words, and then increment the word counter.
                strcpy(words[word_count++], token1);
				words[word_count - 1] = (char*) realloc (words[word_count - 1], strlen(words[word_count - 1]) + 1);
            }
            token2 = strtok_r(NULL, " ", &saveptr2);
        }
        token1 = strtok_r(NULL, " ", &saveptr1);
    }

    // Freeing memory that is no longer needed for the remaining parts of the programme
    free(s2_copy);
    free(s1);
    free(s2);

    // Printing all common words
    printf("Common words:\n");
    for (i = 0; i < word_count; i++) {
        printf("%s\n", words[i]);
    }

    // Freeing all remaining memory
    for (int i = 0; i < word_count; i++) {
		free(words[i]);
	}
	free(words);

	return 0;
}

// Undefining MAX. Is this necessary?
#undef MAX