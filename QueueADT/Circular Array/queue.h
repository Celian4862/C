#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include "student.h"

typedef struct {
    Student *studList;
    int max;
    int rear;
    int front;
} QueueADT;

void initQueue(QueueADT*, int);
QueueADT createQueue(int);
bool isEmpty(QueueADT);
bool isFull(QueueADT);
void makeEmpty(QueueADT*);
bool enqueue(QueueADT*, Student);
bool dequeue(QueueADT*);
Student front(QueueADT*);
void visualise(QueueADT);
void display(QueueADT);

#endif