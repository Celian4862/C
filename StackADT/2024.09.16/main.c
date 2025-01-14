#include <stdio.h>
#include <ctype.h>
#include "stack.h"

int main(int argc, char **argv) {
    Stack s;
    initStack(&s);

    Person p1 = {"Alice", 20, 'F'};
    Person p2 = {"Bob", 25, 'M'};
    Person p3 = {"Charlie", 30, 'M'};

    push(&s, p1);
    push(&s, p2);
    push(&s, p3);

    char choice;
    while (choice != '8') {
        printf("What would you like to do?\n");
        printf("1. Add a person\n");
        printf("2. Remove a person\n");
        printf("3. Display all persons\n");
        printf("4. See top of stack\n");
        printf("5. Add a person, sorted (version 1)\n");
        printf("6. Add a person, sorted (version 2)\n");
        printf("7. Sort persons\n");
        printf("8. Exit\n");
        printf("Enter your choice here: ");
        scanf(" %c", &choice);
        printf("\n");
        
        switch (choice - '0') {
            case 1: {
                Person p;
                printf("Enter name: ");
                scanf(" %s", p.name);
                printf("Enter age: ");
                scanf("%d", &p.age);
                do {
                    printf("Enter sex: (M/F) ");
                    scanf(" %c", &p.sex);
                    if (toupper(p.sex) != 'M' && toupper(p.sex) != 'F') {
                        printf("Invalid input. Please enter 'M' or 'F'.\n");
                    }
                } while (toupper(p.sex) != 'M' && toupper(p.sex) != 'F');
                if (push(&s, p)) {
                    printf("Person added.");
                } else {
                    printf("Failed to add person.");
                }
                break;
            }
            case 2: {
                char c;
                printf("Are you sure you want to remove a person? (y/n): ");
                scanf(" %c", &c);
                if (tolower(c) == 'y') {
                    if (pop(&s)) {
                        printf("Person removed.");
                    } else {
                        printf("Failed to remove person.");
                    }
                }
                break;
            }
            case 3:
                displayStack(s);
                break;
            case 4:
                if (isEmpty(s)) {
                    printf("Stack is empty.");
                } else {
                    Person p = peek(s);
                    printf("Name: %s\nAge: %d\nSex: %c", p.name, p.age, p.sex);
                }
                break;
            case 5: {
                Person p;
                printf("Enter name: ");
                scanf(" %s", p.name);
                printf("Enter age: ");
                scanf("%d", &p.age);
                printf("Enter sex: ");
                scanf(" %c", &p.sex);
                if (insertSorted1(&s, p)) {
                    printf("Person added.");
                } else {
                    printf("Failed to add person.");
                }
                break;
            }
            case 6: {
                Person p;
                printf("Enter name: ");
                scanf(" %s", p.name);
                printf("Enter age: ");
                scanf("%d", &p.age);
                printf("Enter sex: ");
                scanf(" %c", &p.sex);
                if (insertSorted2(&s, p)) {
                    printf("Person added.");
                } else {
                    printf("Failed to add person.");
                }
                break;
            }
            case 7: {
                printf("Would you like to sort the stack in ascending order or descending order? (a/d): ");
                char c;
                scanf(" %c", &c);
                sortStack(&s, tolower(c) == 'a');
                break;
            }
            case 8:
                printf("Goodbye!");
                break;
            default:
                printf("Invalid choice.");
        }
        printf("\n\n");
    }
    while (s != NULL) {
        pop(&s);
    }
    return 0;
}