#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "queue.h"

int main(int argc, char **argv) {
    NQueue nq;
    char choice = '0';
    initNQueue(&nq);
    
    while (choice != 7) {
        printf("\n");
        printf("Choose a queue operation:\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Display queue\n");
        printf("4. See front\n");
        printf("5. Filter queue by last name\n");
        printf("6. Sorted enqueue\n");
        printf("7. Exit\n");
        printf("Enter your choice here: ");
        
        scanf(" %c", &choice);
        printf("\n");
        choice -= '0';

        switch (choice) {
            case 1:
            case 6: {
                printf("Enter first name: ");
                Name name_input;
                scanf(" %29s", name_input.fname);
                printf("Enter last name: ");
                scanf(" %29s", name_input.lname);
                printf("\n");
                switch ((int) choice) {
                    case 1:
                        if (enqueue(&nq, name_input)) {
                            printf("Enqueue successful.\n");
                        } else {
                            printf("Enqueue unsuccessful.\n");
                        }
                        break;
                    case 6:
                        if (insertSorted(&nq, name_input)) {
                            printf("Enqueue successful.\n");
                        } else {
                            printf("Enqueue unsuccessful.\n");
                        }
                        break;
                }
                break;
            }
            case 2:
                printf("Are you sure you want to dequeue? (Y/N) ");
                scanf(" %c", &choice);
                printf("\n");
                if (choice == 'y' || choice == 'Y') {
                    if (dequeue(&nq)) {
                        printf("Dequeue successful.\n");
                    } else {
                        printf("Dequeue unsuccessful.\n");
                    }
                } else if (choice == 'n' || choice == 'N') {
                    printf("Dequeue canceled.\n");
                }
                choice = 2;
                break;
            case 3:
                if (isEmpty(nq)) {
                    printf("The queue is empty.\n");
                } else {
                    displayQueue(nq);
                }
                break;
            case 4: {
                if (isEmpty(nq)) {
                    printf("The queue is empty.\n\n");
                } else {
                    Name temp = front(nq);
                    printf("%s %s\n", temp.fname, temp.lname);
                }
                break;
            }
            case 5: {
                printf("Enter the last name by which you would like to filter the queue: ");
                char lname[30];
                scanf(" %29s", lname);
                printf("\n");
                Name *filtered_names;
                filtered_names = filterNames(&nq, lname);
                printf("The following names have been removed:\n");
                int i;
                for (i = 0; strcmp(filtered_names[i].lname, ""); i++) {
                    printf("%d. %s %s\n", i + 1, filtered_names[i].fname, filtered_names[i].lname);
                }
                free(filtered_names);
                break;
            }
            case 7:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice.\n");
        }
    }

    printf("\n\n");
    return 0;
}