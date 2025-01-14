#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node_t;

Node_t *initialiseNode(int);
Node_t get(int, Node_t*);
void insert(int, int, Node_t*);
void delete(int, Node_t*);
void replace(int, int, Node_t*);
int size(Node_t*);
int isEmpty(Node_t*);
int isFull(Node_t*);
void printList(Node_t*);

int main () {
    Node_t *head = intialiseNode(1);
    Node_t *pointer;
    for (int i = 0; i < 3; i++) {
        pointer = head;
        while (pointer->next != NULL) {
            pointer = pointer->next;
        }
        pointer->next = intialiseNode(i + 2);
    }
    printList(head);
    free(head);
    return 0;
}

Node_t *intialiseNode(int input) {
    Node_t *node = (Node_t *)malloc(sizeof(Node_t));
    node->data = input;
    node->next = NULL;
    return node;
}

Node_t get(int index, Node_t *head) {
    Node_t *current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return *current;
}

void insert(int index, int data, Node_t *head) {
    Node_t *current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    Node_t *newNode = intialiseNode(data);
    newNode->next = current->next;
    current->next = newNode;
}

void delete(int index, Node_t *head) {
    Node_t *current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    Node_t *temp = current->next;
    current->next = current->next->next;
    free(temp);
}

void replace(int index, int data, Node_t *head) {
    Node_t *current = head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    current->data = data;
}

int size(Node_t *head) {
    Node_t *current = head;
    int count = 0;
    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

int isEmpty(Node_t *head) {
    return (head == NULL);
}

int isFull(Node_t *head) {
    return 0;
}

void printList(Node_t *head) {
    Node_t *current = head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}