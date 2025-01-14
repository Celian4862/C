#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *prev;
    struct node *next;
} *node;

node createNewNode(int);
void insertSortedLinkedListElement(node, int);
void printList(node);
node findTrueHead(node);
node findTail(node);
void freeList(node);

int main() {
    int n;
    printf("Enter an integer to store into a linked list: ");
    scanf("%d", &n);
    node head = createNewNode(n);
    printf("How many more integers would you like to insert? (Enter now:) ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        int n1;
        printf("Enter integer %d: ", i + 1);
        scanf("%d", &n1);
        insertSortedLinkedListElement(head, n1);
        head = findTrueHead(head);
    }
    printList(head);

    node tail = findTail(head);
    freeList(tail);
    
    return 0;
}

node createNewNode(int n) {
    node newNode = (node)malloc(sizeof(struct node));
    newNode->data = n;
    newNode->prev = NULL;
    newNode->next = NULL;
    return newNode;
}

void insertSortedLinkedListElement(node head, int n) {
    node newNode = createNewNode(n);
    node trav = head;
    for (; trav->next != NULL; trav = trav->next) {
        if (newNode->data < trav->data) {
            newNode->next = trav;
            newNode->prev = trav->prev;
            if (newNode->prev != NULL) {
                newNode->prev->next = newNode;
            }
            trav->prev = newNode;
            return;
        }
    }
    // The for loop ended before doing checks with the last node in order to ensure the last resort does not cause segmentation fault.
    if (newNode->data < trav->data) {
        newNode->next = trav;
        newNode->prev = trav->prev;
        if (newNode->prev != NULL) {
            newNode->prev->next = newNode;
        }
        trav->prev = newNode;
        return;
    }
    // If the new node is the largest element in the list (i.e. it should be the last element)
    trav->next = newNode;
    newNode->prev = trav;
}

void printList(node head) {
    node trav = head;
    printf("Printing all items in the list:\n");
    for (; trav != NULL; trav = trav->next) {
        printf("%d\n", trav->data);
    }
}

node findTrueHead(node head) {
    node trav = head;
    for (; trav->prev != NULL; trav = trav->prev);
    head = trav;
    return head;
}

node findTail(node head) {
    node trav = head, tail;
    for (; trav->next != NULL; trav = trav->next);
    tail = trav;
    return tail;
}

void freeList(node tail) {
    node trav = tail->prev;
    for (; trav->prev != NULL; trav = trav->prev) {
        free(trav->next);
    }
    // When trav reaches the head
    free(trav);
}