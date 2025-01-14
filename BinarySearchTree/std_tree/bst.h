#ifndef BST_H
#define BST_H
#include <stdbool.h>

// Hidden variable
// void (*display[4])(NodePtr) = {breadth_first, preorder, inorder, postorder};

typedef struct node {
    int data;
    struct node *left;
    struct node *right;
} NodeType, *NodePtr, *BST;

typedef struct queue_node {
    NodePtr node;
    struct queue_node *link;
} QueueNode, *QueuePtr;

typedef struct queue {
    QueuePtr head, tail;
} *QueueADT;

void init(BST*);
bool insert(BST*, int);
void breadth_first(BST);
void preorder(BST);
void inorder(BST);
void postorder(BST);
void allDisplay(BST);

#endif
