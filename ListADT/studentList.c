#include <stdio.h>
#include <string.h>

typedef struct {
    char fName[20], lName[20];
} name;

typedef struct {
    int grade;
    char subjectName[20];
} subjectGrade;

typedef struct {
    int idNum;
    name studentName;
    char course[10];
    subjectGrade studentGrade[3];
} studentInfo;

typedef struct {
    studentInfo studentList[4];
    int count; // count keeps track of how many actual values are inside the array
} classRecord;

studentInfo addNewStudent(char[], char[], char[], int, char[], int, char[], int, char[], int);
void addFront(int[], int*, int);
void addFront_student(classRecord*, studentInfo);

int main() {
    int i = 0;
    // ADT should have the following operations: insert, delete, update, traverse
    // Insert - Insert Front, Insert Last, Insert Into, Insert Sorted
    // Delete - Delete Front, Delete Last, Delete at Position, Delete Item
    /* classRecord record;
    char name[20];
    
    for (i = 0; i < 4; i++) {
        printf("Enter your first name (%d): ", i + 1);
        scanf("%s", name);
        record.studentList[i] = addNewStudent(name, "Elalto", "BSCpE", 13100270, "Prog2", 80, "Web2", 85, "IM2", 90);
        record.count++;
    }

    // Everything above is Insert Last

    printf("OUTPUT:\n");
    for (i = 0; i < 4; i++) {
        printf("%s\n", record.studentList[i].studentName.fName);
    } */

    int x[5] = {1, 2, 3, 4};
    int count = 4;

    addFront(x, &count, 10);
    for (i = 0; i < count; i++) {
        printf("%d ", x[i]);
    }
    printf("\n");

    return 0;
}

studentInfo addNewStudent (char fName[], char lName[], char courseName[], int idNum, char sub1[], int sub1Grade, char sub2[], int sub2Grade, char sub3[], int sub3Grade) {
  studentInfo newStudent;
  
  newStudent.idNum = idNum;
  strcpy(newStudent.studentName.fName, fName);
  strcpy(newStudent.studentName.lName, lName);
  strcpy(newStudent.course, courseName);
  
  strcpy(newStudent.studentGrade[0].subjectName, sub1);
  newStudent.studentGrade[0].grade = sub1Grade;
  
  strcpy(newStudent.studentGrade[1].subjectName, sub2);
  newStudent.studentGrade[1].grade = sub2Grade;
  
  strcpy(newStudent.studentGrade[2].subjectName, sub3);
  newStudent.studentGrade[2].grade = sub3Grade;
  
  printf("%s\n", newStudent.studentName.fName);
  
  return newStudent;
}

void addFront(int arr[], int *count, int toInsert) {
    int i = 0;

    for (i = *count; i > 0; i--) {
        arr[i] = arr[i - 1];
    }

    arr[0] = toInsert;
    (*count)++;
}

void addFront_student(classRecord* record, studentInfo studentToAdd) {
    int i = 0;

    for (i = record->count; i >= 0; i--) {
        record->studentList[i] = record->studentList[i - 1];
    }
}