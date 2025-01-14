#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "student.h"

Name createName(String fname, String lname) {
    Name n;
    strcpy(n.fname, fname);
    strcpy(n.lname, lname);
    return n;
}

Student createStudent(int studID, Name studName, bool sex, String program, int year) {
    Student s;
    s.studID = studID;
    s.studName = studName;
    s.sex = sex;
    strcpy(s.program, program);
    s.year = year;
    return s;
}

void displayStudent(Student s) {
    printf("Student ID: %d\n", s.studID);
    printf("Student Name: %s %s\n", s.studName.fname, s.studName.lname);
    printf("Sex: %c\n", (s.sex) ? 'm' : 'f');
    printf("Program: %s\n", s.program);
    printf("Year: %d\n", s.year);
    printf("\n");
}