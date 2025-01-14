#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

// Structure to represent a stack
typedef struct {
    char data[MAX_SIZE];
    int top;
} Stack;

// Function to initialize the stack
void initialize(Stack* stack) {
    stack->top = -1;
}

// Function to check if the stack is empty
int isEmpty(Stack* stack) {
    return stack->top == -1;
}

// Function to check if the stack is full
int isFull(Stack* stack) {
    return stack->top == MAX_SIZE - 1;
}

// Function to push an element onto the stack
void push(Stack* stack, char element) {
    if (isFull(stack)) {
        printf("Stack overflow!\n");
        exit(1);
    }
    stack->data[++stack->top] = element;
}

// Function to pop an element from the stack
char pop(Stack* stack) {
    if (isEmpty(stack)) {
        printf("Stack underflow!\n");
        exit(1);
    }
    return stack->data[stack->top--];
}

// Function to check if a word is a palindrome
int isPalindrome(char* word) {
    Stack stack;
    initialize(&stack);

    int length = strlen(word);
    int i;

    // Push each character of the word onto the stack
    for (i = 0; i < length; i++) {
        push(&stack, word[i]);
    }

    // Pop each character from the stack and compare with the word
    for (i = 0; i < length; i++) {
        if (pop(&stack) != word[i]) {
            return 0; // Not a palindrome
        }
    }

    return 1; // Palindrome
}

int main() {
    char word[MAX_SIZE];

    printf("Enter a word: ");
    scanf("%s", word);

    if (isPalindrome(word)) {
        printf("%s is a palindrome.\n", word);
    } else {
        printf("%s is not a palindrome.\n", word);
    }

    return 0;
}