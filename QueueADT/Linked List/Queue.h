#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include "MyData.h"

typedef Student Data;

typedef struct node {
    Data elem;
    struct node *link;
} NodeType, *NodePtr;

typedef struct {
    NodePtr head, tail;
} Queue;

void initQueue(Queue *); // Initializes the queue to be empty.
Queue createQueue();
bool isEmpty(Queue); // Returns true if the queue is empty, false otherwise.
void displayQ (Queue); // Displays the elements of the queue.
bool enqueue(Queue *, Data); // Adds an element to the queue. Returns true if successful, false otherwise.
bool dequeue (Queue *); // Removes an element from the queue. Returns true if successful, false otherwise.
Data front (Queue); // Returns the element at the front of the queue.
void makeNull (Queue *); // Removes all elements from the queue.

Name *getStudent(Queue, char *, char); // Gets the names of the students that match the given program and sex. User a name with empty string to denote a terminator for the Names array. If program is an empty string, it means all programs. If sex is empty char, then it means both sexes.

#endif