#include <stdio.h>
#include <string.h>

#define MAX 20

typedef struct {
    char data[MAX];
    int top;
} Stack;

int isEmpty(Stack temp) {
    return temp.top == -1;
}

int isFull(Stack temp) {
    return temp.top == MAX - 1;
}

void push(Stack *temp, char letter) {
    temp->data[++temp->top] = letter;
}

int pop(Stack *temp) {
    char popped = temp->data[temp->top];
    temp->data[temp->top--] = 0;
    return popped;
}

int main() {
    char palindrome[21];
    printf("Enter a word (max 20 characters): ");
    scanf(" %s", palindrome);
    palindrome[20] = 0;
    Stack stack;
    stack.top = -1;
    for (int i = 0; i < strlen(palindrome); i++) {
        push(&stack, palindrome[i]);
    }
    for (int i = 0; i < strlen(palindrome); i++) {
        if (palindrome[i] == pop(&stack)) {
            continue;
        } else {
            printf("It's not a palindrome.\n");
            return 0;
        }
    }
    printf("It's a palindrome.\n");
    return 0;
}