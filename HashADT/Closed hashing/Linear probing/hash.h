#ifndef HASH_H
#define HASH_H

#include <stdbool.h>

typedef enum {
    EMPTY,
    DELETED,
    OCCUPIED
} flag;

typedef struct {
    int studID;
    char studName[30];
    char program[10];
    int year;
} Student;

typedef struct {
    Student stud;
    flag status;
} Hash_idx;

typedef struct {
    Hash_idx *elem; // Dynamically allocate memory for rehashing
    Student *stud_list; // Used when rehashing
    int count, max;
} HashTable;

/*  Get the hash based on the summation of the first 3 letters of the name and the letters in the program.
    Assume that the name is always at least 3 letters long.
    The function must be able to return a value from 0 - 19. */
int getHash(const char*, const char*);

void initDictionary(HashTable*, int);
// Use insertSorted if multiple data are already in the list.
bool insert(HashTable*, Student);
bool deleteItem(HashTable*, Student);

void visualiseTable(HashTable);

void freeHashTable(HashTable*);

#endif