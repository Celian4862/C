#include <stdio.h>
#include <unistd.h>

#define MAX 10

int isEmpty(int top) {
    if (top == -1) {
        return 1;
    } else {
        return 0;
    }
}

void push(int stack[], int *top, int value) {
    if (*top == MAX) {
        printf("Stack is full.\n\n");
        return;
    }
    stack[++(*top)] = value;
    printf("Value added successfully.\n\n");

    sleep(1);
}

int pop(int stack[], int *top) {
    if (isEmpty(*top)) {
        printf("Stack is empty.\n\n");
        sleep(1);
        return 1;
    }
    int value = stack[--(*top)];
    return value;
}

int main() {
    int stack[10], top = -1, choice = 0, value; // Testing with stack size 10
    while (choice != 6) {
        printf("Stack testing programme! Choose a stack process:\n1. Push\n2. Pop\n3. Display Top\n4. Display all\n5. Check if empty\n6. End\nInput here: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Input an integer that you'd like to add: ");
                scanf("%d", &value);
                push(stack, &top, value);
                break;
            case 2:
                printf("Popped value: %d\n\n", pop(stack, &top));
                sleep(1);
                break;
            case 3:
                printf("Top value: %d\n\n", stack[top]);
                sleep(1);
                break;
            case 4:
                for (int i = 0; i < top + 1; i++) {
                    printf("Value %d: %d\n", i + 1, stack[i]);
                }
                sleep(1);
                printf("\n");
                break;
            case 5:
                (isEmpty(top)) ? printf("It's empty.\n\n") : printf("It's not empty.\n\n");
                sleep(1);
                break;
            case 6:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice.\n\n");
                sleep(1);
        }
    }
    return 0;
}