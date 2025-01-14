#include <stdio.h>
#include <string.h>

int main() {
    char s[10];
    printf("Enter a word (max 10 characters): ");
    scanf(" %s", s);
    char copy[strlen(s) + 1];
    for (int i = 0, j = strlen(s) - 1; i < strlen(s) && j >= 0; i++, j--) {
        copy[j] = s[i];
    }
    copy[strlen(s)] = 0;
    if (!strcmp(copy, s)) {
        printf("The word is a palindrome.");
    } else {
        printf("The word is not a palindrome.");
    }
    return 0;
}