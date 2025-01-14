#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 100 // Maximum number of elements in the set

typedef struct {
    int elements[MAX_SIZE];
    int size;
} Set;

// Function to initialize the set
void initialize(Set *set) {
    set->size = 0;
}

// Function to check if an element is in the set
bool contains(Set *set, int element) {
    for (int i = 0; i < set->size; i++) {
        if (set->elements[i] == element) {
            return true;
        }
    }
    return false;
}

// Function to add an element to the set
void add(Set *set, int element) {
    if (set->size < MAX_SIZE && !contains(set, element)) {
        set->elements[set->size++] = element;
        printf("Added %d to the set.\n", element);
    } else {
        printf("Unable to add %d to the set.\n", element);
    }
}

// Function to remove an element from the set
void removeElement(Set *set, int element) {
    for (int i = 0; i < set->size; i++) {
        if (set->elements[i] == element) {
            // Shift elements to fill the gap
            for (int j = i; j < set->size - 1; j++) {
                set->elements[j] = set->elements[j + 1];
            }
            set->size--;
            printf("Removed %d from the set.\n", element);
            return;
        }
    }
    printf("%d not found in the set.\n", element);
}

// Function to print the elements of the set
void printSet(Set *set) {
    printf("Set: { ");
    for (int i = 0; i < set->size; i++) {
        printf("%d ", set->elements[i]);
    }
    printf("}\n");
}

int main() {
    Set mySet;
    initialize(&mySet);

    add(&mySet, 10);
    add(&mySet, 20);
    add(&mySet, 30);
    printSet(&mySet);
    add(&mySet, 20);

    removeElement(&mySet, 20);
    printSet(&mySet);

    return 0;
}