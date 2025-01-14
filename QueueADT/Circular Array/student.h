#ifndef STUDENT_H
#define STUDENT_H

typedef char String[20];

typedef struct{
    String fname, lname;
} Name;

typedef struct {
    int studID;
    Name studName;
    bool sex; // true - male; false - female
    String program;
    int year;
} Student;

Name createName(String, String);
Student createStudent(int, Name, bool, String, int);
void displayStudent(Student);

#endif