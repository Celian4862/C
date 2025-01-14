// Date: 2021/09/16
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "queue.h"

void initNQueue(NQueue *nq) {
    nq->front = 1;
    nq->rear = 0;
}

bool isEmpty(NQueue nq) {
    return (nq.rear + 1) % MAX == nq.front;
}

bool isFull(NQueue nq) {
    return (nq.rear + 2) % MAX == nq.front;
}

void displayQueue(NQueue nq) {
    for (; nq.front != (nq.rear + 1) % MAX; nq.front = (nq.front + 1) % MAX) {
        printf("%s %s\n", nq.elems[nq.front].fname, nq.elems[nq.front].lname);
    }
}

bool enqueue(NQueue *nq, Name n) {
    if (isFull(*nq)) {
        return false;
    }
    nq->rear = (nq->rear + 1) % MAX;
    nq->elems[nq->rear] = n;
    return true;
}

bool dequeue(NQueue *nq) {
    if (isEmpty(*nq)) {
        return false;
    }
    nq->front = (nq->front + 1) % MAX;
    return true;
}

Name front(NQueue nq) {
    return nq.elems[nq.front];
}

Name *filterNames(NQueue *nq, char *filterString) {
    Name *elems = (Name *) malloc(MAX * sizeof(Name));
    int elems_count = 0, final_front;
    for (final_front = (nq->rear + 1) % MAX; nq->front != final_front; nq->front = (nq->front + 1) % MAX) {
        if (strcmp(filterString, nq->elems[nq->front].lname) != 0) {
            enqueue(nq, nq->elems[nq->front]);
        } else {
            strcpy(elems[elems_count].fname, nq->elems[nq->front].fname);
            strcpy(elems[elems_count].lname, nq->elems[nq->front].lname);
            elems_count++;
        }
    }
    strcpy(elems[elems_count].fname, "");
    strcpy(elems[elems_count].lname, "");
    return elems;
}

bool insertSorted(NQueue *nq, Name n) {
    if (isFull(*nq)) {
        return false;
    }
    int final_front;
    for (final_front = (nq->rear + 1) % MAX; nq->front != final_front; nq->front = (nq->front + 1) % MAX) {
        if (strcmp(nq->elems[nq->front].lname, n.lname) >= 0) {
            nq->rear = (nq->rear + 1) % MAX;
            nq->elems[nq->rear] = n;
            break;
        }
        nq->rear = (nq->rear + 1) % MAX;
        nq->elems[nq->rear] = nq->elems[nq->front];
    }
    for (; nq->front != final_front; nq->front = (nq->front + 1) % MAX) {
        nq->rear = (nq->rear + 1) % MAX;
        nq->elems[nq->rear] = nq->elems[nq->front];
    }
    return true;
}