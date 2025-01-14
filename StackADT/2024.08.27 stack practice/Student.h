#ifndef STUDENT_H
#define STUDENT_H

typedef char String[20];

typedef struct {
    int studID;
    String studName;
    String program;
    int year;
} Student;

Student createStudent(int, String, String, int);
void displayStudent(Student);

#endif