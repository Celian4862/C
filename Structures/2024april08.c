#include <stdio.h>
#include <stdlib.h>

typedef struct stud {
    char firstName[10];
} Stud;

typedef struct class {
    int population;
    struct stud *info;
    float *grades; // 3 grades
} Class;

Class populate() {
    Class c;
    printf("Enter how many students are in the class: ");
    scanf("%d", &c.population);
    c.info = (Stud *)malloc(c.population * sizeof(Stud));
    c.grades = (float *)malloc(c.population * sizeof(float));
    int i = 0;
    for (i = 0; i < c.population; i++) {
        printf("Enter the first name of student %d: ", i + 1);
        scanf(" %s", c.info[i].firstName);
        printf("Enter the grades of student %d: ", i + 1);
        scanf("%f", &(c.grades[i]));
    }
    return c;
}

void printStruct(Class c) {
    printf("The class has %d students\n", c.population);
    int i = 0;
    for (i = 0; i < c.population; i++) {
        printf("Student %d: %s\n", i + 1, c.info[i].firstName);
    }
    for (i = 0; i < c.population; i++) {
        printf("Student %d: %.2f\n", i + 1, c.grades[i]);
    }
}

void freeMemory(Class c) {
    free(c.info);
    free(c.grades);
}

int main() {
    Class test = populate();
    printStruct(test);
    freeMemory(test);
}