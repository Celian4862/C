#ifndef MYDATA_H
#define MYDATA_H

typedef struct {
    char fname[20];
    char lname[20];
} Name;

typedef struct {
    int studID;
    Name studName;
    char sex; // 'f' or 'm'
    char program[6];
} Student;

#endif