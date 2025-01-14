#ifndef STACK_H
#define STACK_H
#include <stdbool.h>

typedef struct {
    char name[30];
    int age;
    char sex;
} Person;

typedef struct node {
    Person data;
    struct node *link;
} NodeType, *NodePtr, *Stack;

void initStack(Stack *s);
bool isEmpty(Stack s);
void displayStack(Stack s);

bool push(Stack *s, Person p);
bool pop(Stack *s);
Person peek(Stack s);

// insertSorted based on name. Remember to use the property of the stack using push, pop, and peek functions.
bool insertSorted1(Stack *s, Person p);

// insertSorted based on name. Remember to use the property of the stack without using push, pop, and peek functions.
bool insertSorted2(Stack *s, Person p);

// Sort the values based on name. Use flag for ascending or descending.
void sortStack(Stack *s, bool flag);

#endif