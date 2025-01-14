#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "queue.h"

_Bool check_cancel_input(const char*);
_Bool is_all_digits(const char*);

int main() {
    QueueADT q;
    Student s;
    int max;
    char choice;
    String buffer;
    _Bool invalid_input, cancel_input;
    printf("How many students do you have in total? ");
    while (true) {
        scanf(" %10s", buffer);
        if (!is_all_digits(buffer)) {
            printf("Invalid input. Please try again.\n");
            continue;
        }
        break;
    }
    max = atoi(buffer);
    q = createQueue(max);
    long int stud_size = sizeof(Student);
    long int size = sizeof(Student) * (max + 1);
    printf("\n");
    do {
        cancel_input = false;
        printf("What would you like to do with the queue?\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Empty the queue\n");
        printf("4. See front\n");
        printf("5. Visualise\n");
        printf("6. Display\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);
        printf("\n");
        if (!isdigit(choice)) {
            printf("Invalid choice. Please try again.\n\n");
            continue;
        }
        switch (atoi(&choice)) {
            case 1:
                if (isFull(q)) {
                    break;
                }
                printf("Enter N or n as the first character in your input to cancel enqueueing at any point.\nEnter student details. ");
                // Entering student ID
                while (true) {
                    printf("Enter student ID: ");
                    scanf(" %10s", buffer);
                    cancel_input = check_cancel_input(buffer);
                    if (cancel_input) {
                        break;
                    }
                    if (!is_all_digits(buffer)) {
                        
                        printf("Invalid student ID. Please try again.\n");
                        continue;
                    }
                    break;
                }
                if (cancel_input) {
                    break;
                }
                s.studID = atoi(buffer);

                // Entering student last name
                while (true) {
                    printf("Enter student's last name: ");
                    scanf(" %19s", buffer);
                    cancel_input = check_cancel_input(buffer);
                    if (cancel_input) {
                        break;
                    }
                    printf("Is this the student's last name? (%s) (Y/N) ", buffer);
                    scanf(" %c", &choice);
                    
                    if (choice == 'Y' || choice == 'y') {
                        break;
                    }
                }
                if (cancel_input) {
                    break;
                }
                strcpy(s.studName.lname, buffer);

                // Entering student's first name
                while (true) {
                    printf("Enter student's first name: ");
                    scanf(" %19s", buffer);
                    cancel_input = check_cancel_input(buffer);
                    if (cancel_input) {
                        break;
                    }
                    printf("Is this the student's first name? (%s) (Y/N) ", buffer);
                    scanf(" %c", &choice);
                    if (choice == 'Y' || choice == 'y') {
                        break;
                    }
                }
                if (cancel_input) {
                    break;
                }
                strcpy(s.studName.fname, buffer);

                // Enter student's sex
                while (true) {
                    printf("What is the sex of the student? (M/F) ");
                    scanf(" %c", &choice);
                    cancel_input = check_cancel_input(&choice);
                    if (cancel_input) {
                        break;
                    }
                    if (choice == 'M' || choice == 'm') {
                        s.sex = true;
                    } else if (choice == 'F' || choice == 'f') {
                        s.sex = false;
                    } else {
                        printf("Invalid choice. Please try again.\n");
                        continue;
                    }
                    break;
                }
                if (cancel_input) {
                    break;
                }

                // Enter student's programme
                while (true) {
                    printf("What is the programme of the student? ");
                    scanf(" %19s", buffer);
                    cancel_input = check_cancel_input(buffer);
                    if (cancel_input) {
                        break;
                    }
                    printf("Is this the student's programme? (%s) (Y/N) ", buffer);
                    scanf(" %c", &choice);
                    
                    if (choice == 'Y' || choice == 'y') {
                        break;
                    }
                }
                if (cancel_input) {
                    break;
                }
                strcpy(s.program, buffer);

                // Enter student's year
                while (true) {
                    printf("What year is the student in? ");
                    scanf(" %10s", buffer);
                    cancel_input = check_cancel_input(buffer);
                    if (cancel_input) {
                        break;
                    }
                    if (!is_all_digits(buffer)) {
                        printf("Invalid input. Please try again.\n");
                        continue;
                    }
                    s.year = atoi(buffer);
                    break;
                }
                if (cancel_input) {
                    break;
                }

                enqueue(&q, s);
                break;
            case 2:
                dequeue(&q);
                break;
            case 3:
                if (isEmpty(q)) {
                    break;
                }
                printf("Are you sure you want to empty the queue? (Y/N) ");
                scanf(" %c", &choice);
                if (choice == 'Y' || choice == 'y') {
                    makeEmpty(&q);
                }
                break;
            case 4:
                if (isEmpty(q)) {
                    break;
                }
                displayStudent(front(&q));
                break;
            case 5:
                visualise(q);
                break;
            case 6:
                display(q);
                break;
            case 7:
                printf("Thank you for using the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
        printf("\n");
    } while (atoi(&choice) != 7);

    return 0;
}

_Bool check_cancel_input(const char *str) {
    if (*str == 'N' || *str == 'n') {
        printf("Enqueue canceled.\n");
        return true;
    }
    return false;
}

_Bool is_all_digits(const char *str) {
    while (*str) {
        if (!isdigit(*str)) {
            return false;
        }
        str++;
    }
    return true;
}