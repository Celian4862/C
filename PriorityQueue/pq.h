#ifndef PQ_H
#define PQ_H
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int *arr,
    max,
    lastIdx,
    depth_breadth;
} Heap;

bool initHeap(Heap*);
bool resizeHeap(Heap*);
bool insertHeap(Heap*, int);
bool rmHeap(Heap*);
bool heapify(Heap*);

void breadth_first(Heap, int);
void preorder(Heap, int);
void inorder(Heap, int);
void postorder(Heap, int);

#endif