#include <stdio.h>
#include <stdlib.h>
struct node
{
    int data;
    struct node *next;
};

void printThis(struct node *trav)
{
    while (trav) {
        printf("%d\n", trav->data);
        trav = trav->next;
    }
}

int main() {
    struct node *head = (struct node *)malloc(sizeof(struct node));
    struct node *one =  (struct node *)malloc(sizeof(struct node));
    one->data = 1;
    head->next = one;
    
    struct node *two =  (struct node *)malloc(sizeof(struct node));
    two->data = 2;    
    one->next = two;
    
    struct node *tree =  (struct node *)malloc(sizeof(struct node));
    tree->data = 3;
    tree->next = NULL;
    two->next = tree;

    printf("\n");
    
    printThis(head);

    return 0;
}