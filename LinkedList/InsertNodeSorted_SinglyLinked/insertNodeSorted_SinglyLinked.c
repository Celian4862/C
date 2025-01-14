#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} *node;

node createNewNode(int);
node insertAtHead(node, int);
void insertNodeSorted(node, int);
void printList(node);
void freeList(node);

int main(int argv, char *argc[]) {
    int n, count, i;
    printf("Enter an integer: ");
    scanf("%d", &n);
    node head = createNewNode(n);
    printf("How many more integers would you like to input? ");
    scanf("%d", &count);
    for (i = 0; i < count; i++) {
        printf("Enter integer %d: ", i + 1);
        scanf("%d", &n);
        if (n < head->data) {
            head = insertAtHead(head, n);
            continue;
        }
        insertNodeSorted(head, n);
    }

    printList(head);

    freeList(head);
    return 0;
}

node createNewNode(int data) {
    node temp = (node)malloc(sizeof(struct node));
    temp->data = data;
    temp->next = NULL;
    return temp;
}

node insertAtHead(node head, int data) {
    node newNode = createNewNode(data);
    newNode->next = head;
    head = newNode;
    return head;
}

void insertNodeSorted(node head, int data) {
    node newNode = createNewNode(data), trav = head;
    for (; trav->next != NULL; trav = trav->next) {
        if (newNode->data < trav->next->data) {
            newNode->next = trav->next;
            trav->next = newNode;
            return;
        }
    }
    // This checks the tail node and inserts itself just before the tail if the code block runs, because the for loop ends right before the tail to prevent segmentation fault for the last resort.
    if (newNode->data < trav->data) {
        newNode->next = trav->next;
        trav->next = newNode;
        return;
    }
    // This is the last resort, which makes the node the new tail.
    trav->next = newNode;
}

void printList(node head) {
    node trav = head;
    printf("Printing the list:\n");
    for (; trav != NULL; trav = trav->next) {
        printf("%d\n", trav->data);
    }
}

void freeList(node head) {
    node trav = head->next, to_free = head;
    for (; trav != NULL; trav = trav->next) {
        free(to_free);
        to_free = trav;
    }
    free(to_free);
}