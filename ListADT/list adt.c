/*
Perhaps we can create different list types to test our abilities.
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    void *data;
    struct ListNode *next;
} ListNode;

typedef struct {
    ListNode *head;
    int size;
} List;

List *createList() {
    List *list = malloc(sizeof(List));
    if (list == NULL) {
        // Handle memory allocation failure
        return NULL;
    }
    list->head = NULL;
    list->size = 0;
    return list;
}

void add(List *list, void *data) {
    ListNode *newNode = malloc(sizeof(ListNode));
    if (newNode == NULL) {
        // Handle memory allocation failure
        return;
    }
    newNode->data = data;
    newNode->next = NULL;

    if (list->head == NULL) {
        list->head = newNode;
    } else {
        ListNode *current = list->head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
    list->size++;
}

void *get(List *list, int index) {
    if (index < 0 || index >= list->size) {
        // Handle invalid index
        return NULL;
    }
    ListNode *current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current->data;
}

int main() {
    List *list = createList();
    if (list == NULL) {
        // Handle list creation failure
        return 1;
    }

    int intValue = 42;
    add(list, &intValue);

    double doubleValue = 3.14;
    add(list, &doubleValue);

    char *stringValue = "Hello";
    add(list, stringValue);

    // Retrieving and typecasting values from the list
    printf("Int value: %d\n", *((int *)get(list, 0)));
    printf("Double value: %.2f\n", *((double *)get(list, 1)));
    printf("String value: %s\n", (char *)get(list, 2));

    return 0;
}