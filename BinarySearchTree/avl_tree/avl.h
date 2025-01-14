#ifndef AVL_H
#define AVL_H

typedef struct node {
    int data, left_height, right_height;
    struct node *left, *right;
} *AVL;

#endif