#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

typedef struct {
    int prodID;
    char prodName[16];
    int prodQty;
    float prodPrice;
} Product;

typedef struct node {
    Product prod;
    struct node *link;
} NodeType, *NodePtr, *Stack;

typedef struct {
    NodePtr *data; // Dynamic array
    int count; // 70% packing density
    int max;
} ProdDict;

// Stack ADT operations
void initStack(Stack*);
bool isEmpty(Stack);
bool push(Stack*, Product);
bool pop(Stack*);
Product peek(Stack);
void visualiseStack(Stack);

// Hash table operations
void initDict(ProdDict*, int);
int getHash(int, char*, int);
Product getDict(ProdDict, int, char*); // Check if prodID of returned value is -1, then the given item doesn't exist
bool addDict(ProdDict*, Product);
bool removeDict(ProdDict*, int, char*);
void visualiseDict(ProdDict);
void stackToDict(ProdDict*, Stack*);

#endif