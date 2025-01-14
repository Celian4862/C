#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "stack.h"

void initStack(Stack *s) {
    *s = NULL;
}

bool isEmpty(Stack s) {
    return s == NULL;
}

void displayStack(Stack s) {
    if (isEmpty(s)) {
        printf("Stack is empty.");
        return;
    }
    while (s != NULL) {
        printf("Name: %s\nAge: %d\nSex: %c\n\n", s->data.name, s->data.age, s->data.sex);
        s = s->link;
    }
}

bool push(Stack *s, Person p) {
    Stack new_node = (Stack) malloc(sizeof(NodeType));
    if (new_node == NULL) {
        return false;
    }
    new_node->data = p;
    new_node->link = *s;
    *s = new_node;
    return true;
}

bool pop(Stack *s) {
    if (isEmpty(*s)) {
        return false;
    }
    Stack temp = *s;
    *s = (*s)->link;
    free(temp);
    return true;
}

Person peek(Stack s) {
    return s->data;
}

/*
Error message:
double free or corruption (out)
Aborted (core dumped)
*/
bool insertSorted1(Stack *s, Person p) {
    Stack s2;
    while (*s != NULL) {
        if (strcmp(p.name, (*s)->data.name) < 0) {
            if (!push(s, p)) {
                return false;
            }
            break;
        }
        push(&s2, (*s)->data);
        pop(s);
    }
    while (s2 != NULL) {
        push(s, s2->data);
        pop(&s2);
    }
}

// Error: does not add the new node to the stack
bool insertSorted2(Stack *s, Person p) {
    Stack s2, temp, new_node;
    while (*s != NULL) {
        if (strcmp(p.name, (*s)->data.name) < 0) {
            new_node = (Stack) malloc (sizeof(NodeType));
            if (new_node == NULL) {
                return false;
            }
            new_node->data = p;
            new_node->link = *s;
            *s = new_node;
            break;
        }
        temp = *s;
        *s = (*s)->link;
        temp->link = s2;
        s2 = temp;
    }
    while (s2 != NULL) {
        temp = s2;
        s2 = s2->link;
        temp->link = *s;
        *s = temp;
    }
    return true;
}

void sortStack(Stack *s, bool flag) {

}