#include <stdio.h>
#include <stdlib.h>
struct node
{
    int data;
    struct node *next;
};

void printThis(struct node *trav)
{
    while (trav->next!=NULL)
    {
        trav = trav->next;
        printf("%i\n", trav->data);
    }
}

void insertNode(struct node *trav, int data)
{
    struct node *new =  (struct node *)malloc(sizeof(struct node));
    new->data = data;
    new->next = NULL;

    if(trav->next == NULL)//checking if the list is empty
    {
        trav->next = new;
    }
    else // will executed if the list is not empty
    {
        for(;trav->next!=NULL;trav=trav->next){}
            trav->next=new;
    }
    
}

void insertNodeSorted(struct node *trav, int data)
{
    ////as you insert, make sure to insert it at the proper sequence that would result to a sorted list (ascending)
}

void deleteNodeAtEnd()
{
    
}

void deleteNodeByValue(struct node *trav, int value)
{
    
}


int main() {
    struct node *head = (struct node *)malloc(sizeof(struct node));
    head->next = NULL;
    insertNode(head, 1);
    insertNode(head, 2);
    insertNode(head, 3);
    insertNode(head, 4);
    printThis(head);
    return 0;
}