#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure for stack node
struct Node {
    char data;
    struct Node* next;
};

// Function to create a new node
struct Node* newNode(char data) {
    struct Node* node = (struct Node*)malloc(sizeof(struct Node));
    node->data = data;
    node->next = NULL;
    return node;
}

// Function to push a character to the stack
void push(struct Node** top, char data) {
    struct Node* node = newNode(data);
    node->next = *top;
    *top = node;
}

// Function to pop a character from the stack
char pop(struct Node** top) {
    if (*top == NULL) {
        printf("Stack is empty.\n");
        return '\0';
    }
    struct Node* temp = *top;
    char data = temp->data;
    *top = (*top)->next;
    free(temp);
    return data;
}

// Function to check if a word is a palindrome
int isPalindrome(char* word) {
    int len = strlen(word);
    struct Node* stack = NULL;

    // Push each character of the word to the stack
    for (int i = 0; i < len; i++) {
        push(&stack, word[i]);
    }

    // Pop each character from the stack and compare with the word
    for (int i = 0; i < len; i++) {
        char data = pop(&stack);
        if (data != word[i]) {
            return 0; // Not a palindrome
        }
    }

    return 1; // Palindrome
}

int main() {
    char word[21];
    printf("Enter a word (max 20 characters): ");
    scanf("%20s", word);

    if (isPalindrome(word)) {
        printf("%s is a palindrome.\n", word);
    } else {
        printf("%s is not a palindrome.\n", word);
    }

    return 0;
}