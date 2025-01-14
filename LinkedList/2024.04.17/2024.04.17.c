#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int data;
    struct node *next;
} NodeType, *NodePtr;

int get_value();
void printMenu(int*);
NodePtr createNode(int);
void addToEnd(NodePtr, int);
void addToStart(NodePtr, int);
void insertSorted(NodePtr, int);
void deleteByValue(NodePtr, int);
void deleteByPosition(NodePtr, int);
void updateByValue(NodePtr, int, int);
void updateByPosition(NodePtr, int, int);
void displayAll(NodePtr);
void freeList(NodePtr);

int main() {
    NodePtr head = createNode(0);
    int choice = 0;
    while (choice != 9) {
        printMenu(&choice);
        if (choice < 1 || choice > 9) {
            printf("Invalid choice\n");
            continue;
        }
        int value;
        switch (choice) {
            case 1:
                value = get_value();
                addToEnd(head, value);
                break;
            case 2:
                value = get_value();
                addToStart(head, value);
                break;
            case 3:
                value = get_value();
                insertSorted(head, value);
                break;
            case 4:
                value = get_value();
                deleteByValue(head, value);
                break;
            case 5:
                value = get_value();
                deleteByPosition(head, value);
                break;
            case 6:
                value = get_value();
                updateByValue(head, value, get_value());
                break;
            case 7:
                value = get_value();
                updateByPosition(head, value, get_value());
                break;
            case 8:
                displayAll(head);
                break;
            case 9:
                freeList(head);
                break;
        }
    }
    return 0;
}

int get_value() {
    int value;
    printf("Enter a value: ");
    scanf("%d", &value);
    return value;
}

void printMenu(int *choice) {
    printf("1. Add at the end\n2. Add at the start\n3. Insert Sorted\n4. Delete by Value\n5. Delete by Position\n6. Update by Value\n7. Update by Position\n8. Display all\n9. Exit\n");
    scanf("%d", choice);
}

NodePtr createNode(int value) {
    NodePtr newNode = (NodePtr)malloc(sizeof(NodeType));
    if (newNode == NULL) {
        return newNode;
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

void addToEnd(NodePtr head, int value) {
    NodePtr newNode = createNode(value);
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    NodePtr temp = head;
    for (; temp->next != NULL; temp = temp->next);
    temp->next = newNode;
}

void addToStart(NodePtr head, int value) {
    NodePtr newNode = createNode(value);
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    newNode->next = head->next;
    head->next = newNode;
}

void insertSorted(NodePtr head, int value) {
    NodePtr newNode = createNode(value);
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    NodePtr temp = head;
    while (temp->next != NULL && temp->next->data < value) {
        temp = temp->next;
    }
    newNode->next = temp->next;
    temp->next = newNode;
}

void deleteByValue(NodePtr head, int value) {
    NodePtr temp = head;
    while (temp->next != NULL && temp->next->data != value) {
        temp = temp->next;
    }
    if (temp->next == NULL) {
        printf("Value not found\n");
        return;
    }
    NodePtr delNode = temp->next;
    temp->next = delNode->next;
    free(delNode);
}

void deleteByPosition(NodePtr head, int position) {
    NodePtr temp = head;
    for (int i = 0; i < position - 1 && temp->next != NULL; i++) {
        temp = temp->next;
    }
    if (temp->next == NULL) {
        printf("Position not found\n");
        return;
    }
    NodePtr delNode = temp->next;
    temp->next = delNode->next;
    free(delNode);
}

void updateByValue(NodePtr head, int oldValue, int newValue) {
    NodePtr temp = head->next;
    while (temp != NULL && temp->data != oldValue) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Value not found\n");
        return;
    }
    temp->data = newValue;
}

void updateByPosition(NodePtr head, int position, int newValue) {
    NodePtr temp = head->next;
    for (int i = 0; i < position && temp != NULL; i++) {
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Position not found\n");
        return;
    }
    temp->data = newValue;
}

void displayAll(NodePtr head) {
    NodePtr temp = head->next;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

void freeList(NodePtr head) {
    NodePtr temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }
}