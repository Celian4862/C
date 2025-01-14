#include <stdio.h>

int add(int, int);
int subtract(int, int);
int multiply(int, int);
int divide(int, int);

int main() {
    int a, b, op, (*operations[4])(int, int) = {add, subtract, multiply, divide};
    printf("This is a simple calculator between two integers. Enter your desired operation:\n1 Addition\n2 Subtraction\n3 Multiplication\n4 Division\n");
    do {
        printf("Input: ");
        scanf("%d", &op);
        if (op > 4 || op < 1) printf("Invalid input.\n");
    } while (op > 4 || op < 1);
    printf("Enter the two numbers (space-separated): ");
    scanf("%d %d", &a, &b);
    printf("Result: %d\n", operations[op - 1](a, b));
    return 0;
}

int add (int a, int b) {
    return a + b;
}

int subtract (int a, int b) {
    return a - b;
}

int multiply (int a, int b) {
    return a * b;
}

int divide (int a, int b) {
    if (b != 0) return a / b;
    else {
        printf("Zero division error.\n");
        return 0;
    }
}