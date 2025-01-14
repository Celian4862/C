#include "pq.h"

extern void (*display[])(Heap, int);

bool initHeapArray(Heap**, int);
bool resizeHeapArray(Heap**, int);

int main(int argc, char **argv) {
    int numberOfArrs = 1,
    maxArrs = 5,
    arr = 0,
    choice,
    data,
    i;
    Heap *heap;
    if (!initHeapArray(&heap, maxArrs)) {
        return 1;
    }
    if (!initHeap(heap)) {
        return 2;
    }
    do {
        if (numberOfArrs > 1) {
            printf("\nWhich set of data would you like to modify? (1 - %d) ", numberOfArrs);
            scanf("%d", &arr);
            if (arr < 1 || arr > numberOfArrs) {
                printf("Invalid choice.\n\n");
                continue;
            }
            arr--; // Subtract one from array for array indexing
        }
        printf("\nWhat would you like to do?\n1. Insert\n2. Remove\n3. Display data\n4. Add another set of data\n5. Switch heap\n6. Exit\nEnter your choice: ");
        scanf("%d", &choice);
        if (choice < 1 || choice > 5) {
            printf("\nInvalid choice.\n\n");
            continue;
        }
        switch (choice) {
            case 1:
                printf("Enter the datum: ");
                scanf("%d", &data);
                printf("%s\n", (insertHeap(heap + arr, data)) ? "\nInsert successful!\n" : "\nInsert failed.\n");
                break;
            case 2:
                printf("%s\n", (rmHeap(heap + arr)) ? "\nRemove successful!\n" : "\nRemove failed.\n");
                break;
            case 3:
                printf("\nIn which manner would you like to display it?\n1. Breadth-first search\n2. Pre-order depth-first search\n3. In-order depth-first search\n4. Post-order depth-first search\nEnter your choice here: ");
                scanf("%d", &choice);
                if (choice < 1 || choice > 6) {
                    printf("Invalid input.\n\n");
                    break;
                }
                printf("\n");
                display[choice - 1](heap[arr], 0); // Only breadth-first display doesn't need new index arguments; the other three are recursive
                printf("\n");
                /*
                Breadth-first: Prints every datum in the array
                Depth-first: Passes the array for reference as well as the index of the next datum to print
                */
                break;
            case 4: // Add another array
                if (numberOfArrs == maxArrs) {
                    maxArrs += 5;
                    if (!resizeHeapArray(&heap, maxArrs)) {
                        return 1;
                    }
                }
                if (!initHeap(heap + numberOfArrs)) {
                    break;
                }
                numberOfArrs++;
                do {
                    printf("How many elements would you like to put in the array? (Min of 0, max of 15. Heapify will be executed on this array.) ");
                    scanf("%d", &heap[numberOfArrs - 1].lastIdx);
                } while (heap[numberOfArrs - 1].lastIdx < 0 || heap[numberOfArrs - 1].lastIdx > 15);
                heap[numberOfArrs - 1].lastIdx--;
                printf("\n");
                for (i = 0; i < heap[numberOfArrs - 1].lastIdx + 1; i++) {
                    printf("Element %d: ", i + 1);
                    scanf("%d", &heap[numberOfArrs - 1].arr[i]);
                }
                printf("%s\n", (heapify(heap + (numberOfArrs - 1))) ? "Heapify successful!" : "Heapify failed.");
            case 5:
            case 6:
                break;
            default:
                printf("\nInvalid choice.\n\n");
        }
    } while (choice != 6 || choice == 5);
    printf("Goodbye!\n");
    for (int i = 0; i < numberOfArrs; i++) {
        free(heap[i].arr);
    }
    free(heap);
    return 0;
}

bool initHeapArray(Heap **h, int max) {
    *h = (Heap*) malloc (sizeof(Heap) * max);
    if (!(*h)) {
        printf("Memory allocation failed.\n");
        return false;
    }
    return true;
}

bool resizeHeapArray(Heap **h, int max) {
    *h = (Heap*) realloc (*h, sizeof(Heap) * max);
    if (!(*h)) {
        printf("Memory allocation failed.\n");
        return false;
    }
    return true;
}