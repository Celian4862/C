// Incomplete program for Set ADT

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "set_operations.h"

int main () {
    /*  *sets: dynamically created set array for multiple possible sets created by the user
        set_result: resulting set in set operations (union, intersection, difference, symmetric difference) */
    Set *sets = NULL, set_result;
    /*  set_count: current number of sets
        set_index: user's chosen set to perform operations on (cases 1 - 10)
        set_index2: used in comparison operations (cases 5 - 9)
        element: store user's inputted element
        i: loop counter */
    int set_count = 0, set_index = 1, set_index2 = 1, element, i;
    char choice;
    printf("Welcome to the Set ADT program!\n");
    while (choice != 'l') {
        printf("What would you like to do?\n");
        printf("a. Create a set\n");
        printf("b. Add an element to a set\n");
        printf("c. Remove an element from a set\n");
        printf("d. Display a set\n");
        printf("e. Check if an element is in a set\n");
        printf("f. Check if a set is a subset of another set\n");
        printf("g. Find the union of two sets\n");
        printf("h. Find the intersection of two sets\n");
        printf("i. Find the difference of two sets\n");
        printf("j. Find the symmetric difference of two sets\n");
        printf("k. Destroy a set\n");
        printf("l. Exit\n");
        printf("Enter here: ");
        scanf(" %c", &choice);
        choice = tolower(choice);

        switch (choice - 'a') {
            case 0:
                if (!set_count) {
                    sets = (Set *) malloc(sizeof(Set));
                    printf("Creating the first set...\n");
                    set_count++;
                } else {
                    sets = (Set *) realloc(sets, (++set_count) * sizeof(Set));
                    printf("Creating set %d...\n", set_count);
                }
                break;
            case 1:
                set_index = 1;
                if (set_count > 1) {
                    do {
                        printf("Which set would you like to add to? (1-%d) ", set_count);
                        scanf("%d", &set_index);
                        if (set_index < 1 || set_index > set_count) {
                            printf("Invalid set index\n");
                        }
                    } while (set_index < 1 || set_index > set_count);
                    
                }
                printf("What element would you like to add? ");
                scanf("%d", &element);
                if (addElement(&sets[set_index - 1], element)) {
                    printf("Element added\n");
                } else {
                    printf("Element doesn't exist.\n");
                }
                break;
            case 2:
                set_index = 1;
                if (set_count > 1) {
                    do {
                        printf("Which set would you like to remove from? (1-%d) ", set_count);
                        scanf("%d", &set_index);
                        if (set_index < 1 || set_index > set_count) {
                            printf("Invalid set index.\n");
                        }
                    } while (set_index < 1 || set_index > set_count);
                }
                printf("What element would you like to remove? ");
                scanf("%d", &element);
                if (removeElement(&sets[set_index], element)) {
                    printf("Element removed\n");
                } else {
                    printf("Element doesn't exist.\n");
                }
                break;
            case 3:
                set_index = 1;
                if (set_count > 1) {
                    do {
                        printf("Which set would you like to display? (1-%d) ", set_count);
                        scanf("%d", &set_index);
                        if (set_index < 1 || set_index > set_count) {
                            printf("Invalid set index.\n");
                        }
                    } while (set_index < 1 || set_index > set_count);
                }
                displaySet(sets[set_index - 1]);
                break;
            case 4:
                set_index = 1;
                if (set_count > 1) {
                    do {
                        printf("Which set would you like to check? (1-%d) ", set_count);
                        scanf("%d", &set_index);
                        if (set_index < 1 || set_index > set_count) {
                            printf("Invalid set index.\n");
                        }
                    } while (set_index < 1 || set_index > set_count);
                }
                printf("What element would you like to check for? ");
                scanf("%d", &element);
                if (isElement(sets[set_index - 1], element)) {
                    printf("Element exists in the set.\n");
                } else {
                    printf("Element doesn't exist in the set.\n");
                }
                break;
            case 5:
                if (set_count < 2) {
                    printf("There is only one set.\n");
                }
                set_index = 1;
                do {
                    printf("Which sets would you like to compare? (1-%d) (1-%d) ", set_count, set_count);
                    scanf("%d %d", &set_index, &set_index2);
                    if (set_index < 1 || set_index > set_count || set_index2 < 1 || set_index2 > set_count) {
                        printf("Invalid set index(es).\n");
                    }
                } while (set_index < 1 || set_index > set_count || set_index2 < 1 || set_index2 > set_count);
                if (isSubset(sets[set_index - 1], sets[set_index2 - 1])) {
                    printf("The first set is a subset of the second set.\n");
                } else {
                    printf("The first set is not a subset of the second set.\n");
                }
                break;
            case 6:
                if (set_count < 2) {
                    printf("There is only one set.\n");
                }
                break;
            case 10: // Incomplete
                set_index = 1;
                printf("Which set would you like to destroy?\n");
                break;
            case 11:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid choice.\n\n");
        }
    }
    for (i = 0; i < set_count; i++) {
        freeSet(&sets[i]);
    }
    free(sets);

    return 0;
}