#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node
typedef struct Node {
    int data;
    struct Node* next;
} node_t;

struct Node * createNode(int);
void print_list(struct Node *);

int main() {
    // Create nodes
    struct Node* head = createNode(1);
    struct Node* second = createNode(2);
    struct Node* third = createNode(3);

    // Link the nodes
    head->next = second;
    second->next = third;

    // Accessing elements
    printf("Elements in the linked list: %d, %d, %d\n", head->data, second->data, third->data);
    
    print_list(head);

    // Don't forget to free memory when you're done
    free(head);
    free(second);
    free(third);

    return 0;
}

// Function to create a new node
struct Node* createNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
    	return newNode;
    }
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

// Function to print all items in the list
void print_list(node_t * head) {
    node_t * current = head;

    while (current != NULL) {
        printf("%d\n", current->data);
        current = current->next;
    }
}
