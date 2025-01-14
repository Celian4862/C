#ifndef QUEUE_H
#define QUEUE_H
#define MAX 10

#include <stdbool.h>

typedef struct {
    char fname[30];
    char lname[30];
} Name;

typedef struct {
    Name elems[MAX];
    int front;
    int rear;
} NQueue;

void initNQueue(NQueue *nq);
bool isEmpty(NQueue nq);
bool isFull(NQueue nq);
void displayQueue(NQueue nq);

bool enqueue(NQueue *nq, Name n);
bool dequeue(NQueue *nq);
Name front(NQueue nq);

Name *filterNames(NQueue *nq, char *filterString);

/*Insert sorted base on lastname. Remember to use the property 
  of the queue but without using the functions (enqueue, dequeue, front)*/
bool insertSorted(NQueue *nq, Name n);

#endif