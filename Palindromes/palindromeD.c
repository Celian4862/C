#include <stdio.h>
#include <string.h>

int main() {
    char palindrome[21];
    printf("Enter a word: ");
    scanf(" %20s", palindrome);
    int length = strlen(palindrome), isPalindrome = 1;
    for (int i = 0, j = length - 1; i < length / 2; i++, j--) {
        if (palindrome[i] == palindrome[j]) {
            continue;
        } else {
            isPalindrome = 0;
            break;
        }
    }
    (isPalindrome) ? printf("It is a palindrome.\n") : printf("It is not a palindrome.\n");
    return 0;
}