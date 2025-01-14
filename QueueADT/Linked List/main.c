#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "Queue.h"

int main() {
    Queue q = createQueue();
    Data d;
    printf("Welcome to the Queue ADT program.\n");
    int choice;
    do {
        printf("\nWhat would you like to do?\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display\n");
        printf("4. See queue front\n");
        printf("5. Empty queue\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf("\n");
        switch (choice) {
            case 1:
                printf("Enter student ID: ");
                scanf("%d", &d.studID);
                printf("Enter student first name: ");
                scanf(" %s", d.studName.fname);
                printf("Enter student last name: ");
                scanf(" %s", d.studName.lname);
                while (true) {
                    printf("Enter student's sex: ");
                    scanf(" %c", &d.sex);
                    if (tolower(d.sex) != 'm' && tolower(d.sex) != 'f') {
                        printf("Invalid sex. Please try again.\n");
                    } else {
                        break;
                    }
                }
                d.sex = tolower(d.sex);
                printf("Enter student's program: ");
                scanf(" %s", d.program);
                enqueue(&q, d);
                break;
            case 2:
                dequeue(&q);
                break;
            case 3:
                displayQ(q);
                break;
            case 4:
                front(q);
                break;
            case 5:
                makeNull(&q);
                break;
            case 6:
                printf("Thank you for using this programme! Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 6);
    return 0;
}