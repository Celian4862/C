#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

char *initialise_string(int); // Int for size of string
void get_string(char*, int, int); // Char pointer for uninitialised array, int for mode: 0 for no space, 1 for with space
void resize_string(char*, int); // Char pointer for string, int for new size

int main() {
    // Initialise and get strings
    char *s1 = initialise_string(MAX), *s2 = initialise_string(MAX);
    printf("Enter a word or sentence (max 99 characters): ");
    get_string(s1, MAX, 1);
    printf("Enter another word or sentence (max 99 characters): ");
    get_string(s2, MAX, 1);
    // Resize strings
    resize_string(s1, strlen(s1) + 1);
    resize_string(s2, strlen(s2) + 1);
    // Find common words
    
    return 0;
}

void get_string(char *string, int size, int mode) {
    (mode) ? scanf(" %s", string) : scanf(" %[^\n]", string);
    string[size - 1] = 0;
}

char *initialise_string(int size) {
    char *string = (char*)malloc(size * sizeof(char));
    if (string == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }
    return string;
}

void resize_string(char *string, int size) {
    string = (char*)realloc(string, size * sizeof(char));
    if (string == NULL) {
        printf("Memory reallocation failed.\n");
        exit(1);
    }
}