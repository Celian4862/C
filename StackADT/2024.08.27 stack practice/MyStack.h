#ifndef MYSTACK_H
#define MYSTACK_H

#include <stdio.h>
#include <string.h>

#include <stdbool.h>
#include "Student.h"

#define MAX 5

typedef struct {
    Student elems[MAX];
    int count;
} Stack;

Stack createStack();
void initStack(Stack*);
bool isEmpty(Stack);
bool isFull(Stack);
void visualise(Stack);
bool push(Stack*, Student);
bool pop(Stack*);
Student peek(Stack);

Stack getStudent(Stack, String);
void sortStudent(Stack *s);

Stack createStack() {
    Stack s;
    s.count = 0;
    return s;
}

void initStack(Stack *s) {
    s->count = 0;
}

bool isEmpty(Stack s) {
    return s.count == 0;
}

bool isFull (Stack s) {
    return s.count >= MAX;
}

void visualise (Stack s) {
    printf("List {");
    for (int i = 0; i < s.count; ++i) {
        displayStudent(s.elems[i]);
        if (i < s.count - 1) {
            printf("\n");
        }
    }
    printf("}\n");
}

bool push (Stack *s, Student elem) {
    if (!isFull(*s)) {
        s->elems[(s->count)++] = elem;
        return true;
    }
    return false;
}

bool pop (Stack *s) {
    if (!isEmpty(*s)) {
        (s->count)--;
        return true;
    }
    return false;
}

Student peek(Stack s) {
    return s.elems[s.count];
}

Stack getStudent(Stack s, String program) {
    Stack result = createStack();
    for (int i = 0; i < s.count; ++i) {
        if (strcmp(s.elems[i].program, program) == 0) {
            push(&result, s.elems[i]);
        }
    }
    return result;
}

void sortStudent(Stack *s) {
    for (int i = 0; i < s->count; ++i) {
        for (int j = i + 1; j < s->count; ++j) {
            if (s->elems[i].year > s->elems[j].year) {
                Student temp = s->elems[i];
                s->elems[i] = s->elems[j];
                s->elems[j] = temp;
            }
        }
    }
}

Student createStudent(int studID, String studName, String program, int year) {
    Student s;
    s.studID = studID;
    strcpy(s.studName, studName);
    strcpy(s.program, program);
    s.year = year;
    return s;
}

void displayStudent(Student s) {
    printf("Student ID: %d\n", s.studID);
    printf("Student Name: %s\n", s.studName);
    printf("Program: %s\n", s.program);
    printf("Year: %d\n", s.year);
}

#endif