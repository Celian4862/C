#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hash.h"

int getHash(const char *studName, const char *program, int max) {
    int hash = 0;
    for (int i = 0; i < 3; i++) {
        hash += (int) studName[i];
    }
    for (int i = 0; i < strlen(program); i++) {
        hash += (int) program[i];
    }
    return hash % max;
    // 0 <= remainder < divisor
}

void initDictionary(HashTable *ht, int max) {
    ht->elem = (Hash_idx*) malloc (sizeof(Hash_idx) * max);
    ht->count = 0;
    ht->max = max;
    ht->stud_list = (Student *) malloc (sizeof(Student) * max);
    int i;
    for (i = 0; i < max; i++) {
        ht->elem[i].status = EMPTY;
    }
}

bool insert(HashTable *ht, Student s) {
    int hash = getHash(s.studName, s.program, ht->max), double_max = ht->max * 2, i, j;
    Hash_idx *new_elem_array;
    Student *new_stud_list;

    // REHASH
    if (ht->count == 0.65 * ht->max) {
        new_elem_array = (Hash_idx*) realloc (ht->elem, sizeof(Hash_idx) * double_max);
        if (!new_elem_array) {
            printf("Could not reallocate memory.\n");
            return false;
        }
        
        new_stud_list = (Student*) realloc(ht->stud_list, sizeof(Student) * double_max);
        if (!new_stud_list) {
            printf("Could not reallocate memory for student list.\n");
            // Attempt to revert ht->elem to its original size
            new_elem_array = (Hash_idx*) realloc(ht->elem, sizeof(Hash_idx) * ht->max);
            if (!new_elem_array) {
                printf("Critical error: could not revert memory allocation for elements.\n");
                freeHashTable(ht);
                exit(EXIT_FAILURE);
                return false;
            }
            ht->elem = new_elem_array;
            return false;
        }

        ht->elem = new_elem_array;
        ht->stud_list = new_stud_list;
        ht->max = double_max;
        for (i = 0; i < double_max; i++) {
            ht->elem[i].status = EMPTY;
        }

        for (i = 0; i < ht->count; i++) {
            for (j = getHash(ht->stud_list[i].studName, ht->stud_list[i].program, ht->max); ht->elem[j].status != EMPTY; j = (j + 1) % ht->max) {}
            ht->elem[j].stud = ht->stud_list[i];
        }
        hash = getHash(s.studName, s.program, ht->max);
    }
    for (i = hash; ht->elem[i].status != EMPTY; i = (i + 1) % ht->max) {}
    ht->elem[i].stud = s;
    ht->elem[i].status = OCCUPIED;
    ht->stud_list[ht->count++] = s;
    return true;
}

bool deleteItem(HashTable *ht, Student s) {
}

void visualiseTable(HashTable ht) {
}

void freeHashTable(HashTable *ht) {
    free(ht->elem);
    free(ht->stud_list);
}