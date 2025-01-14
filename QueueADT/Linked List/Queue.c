#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "Queue.h"

void initQueue(Queue *q) {
    q->head = q->tail = NULL;
}

Queue createQueue() {
    Queue q;
    q.head = q.tail = NULL;
    return q;
}

bool isEmpty(Queue q) {
    return q.head == NULL;
}

void displayQ (Queue q) {
    if (isEmpty(q)) {
        printf("Queue is empty.\n");
        return;
    }
    while (q.head) {
        printf("%d; %s %s; %c; %s\n", q.head->elem.studID, q.head->elem.studName.fname, q.head->elem.studName.lname, q.head->elem.sex, q.head->elem.program);
        q.head = q.head->link;
    }
}

bool enqueue(Queue *q, Data d) {
    NodePtr temp = (NodePtr) malloc(sizeof(NodeType));
    if (temp == NULL) {
        printf("Memory allocation failed.\n");
        return false;
    }
    temp->elem = d;
    temp->link = NULL;
    if (q->tail == NULL) {
        q->head = temp;
    } else {
        q->tail->link = temp;
    }
    q->tail = temp;
    printf("Enqueued successfully.\n");
    return true;
}

bool dequeue (Queue *q) {
    if (isEmpty(*q)) {
        printf("Queue is empty.\n");
        return false;
    }
    printf("Are you sure you want to dequeue %d; %s %s; %c; %s? (y/n) ", q->head->elem.studID, q->head->elem.studName.fname, q->head->elem.studName.lname, q->head->elem.sex, q->head->elem.program);
    char c;
    scanf(" %c", &c);
    if (c != 'y' && c != 'Y') {
        return false;
    }
    NodePtr temp = q->head;
    q->head = q->head->link;
    free(temp);
    if (q->head == NULL) {
        q->tail = NULL;
    }
    printf("Dequeued successfully.\n");
    return true;
}

Data front (Queue q) {
    Data d;
    if (q.head == NULL) {
        printf("Queue is empty.\n");
        d.studID = -1;
    } else {
        d = q.head->elem;
        printf("%d; %s %s; %c; %s\n", d.studID, d.studName.fname, d.studName.lname, d.sex, d.program);
    }
    return d;
}

void makeNull (Queue *q) {
    if (isEmpty(*q)) {
        printf("Queue is empty.\n");
        return;
    }
    printf("Are you sure you want to empty the queue? (y/n) ");
    char c;
    scanf(" %c", &c);
    if (c != 'y' && c != 'Y') {
        return;
    }
    NodePtr p;
    while (q->head != NULL) {
        p = q->head;
        q->head = q->head->link;
        free(p);
    }
    q->head = q->tail = NULL;
    printf("Queue has been emptied.\n");
}

Name *getStudent(Queue q, char *program, char sex) {
    while (q.head != NULL) {
        if ((strcmp(q.head->elem.program, program) == 0 || strcmp(program, "") == 0) && (q.head->elem.sex == sex || sex == ' ')) {
            printf("%s %s\n", q.head->elem.studName.fname, q.head->elem.studName.lname);
        }
        q.head = q.head->link;
    }
}