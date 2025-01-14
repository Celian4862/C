#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hash.h"

int getHash(Student s) {
    int hash = 0;
    for (int i = 0; i < 3; i++) {
        hash += (int) s.studName[i];
    }
    for (int i = 0; i < strlen(s.program); i++) {
        hash += (int) s.program[i];
    }
    return hash % 20;
    // 0 <= remainder < divisor
}

void initDictionary(HashTable *ht) {
    int i;
    for (i = 0; i < 20; i++) {
        ht->elem[i] = NULL;
    }
    ht->count = 0;
}

bool insert(HashTable *ht, Student s) {
    if (ht->count == 13) {
        return false;
    }
    if (!(ht->elem[getHash(s)])) {
        ht->count++;
    }
    NodePtr *temp;
    for (temp = ht->elem + getHash(s); *temp != NULL; temp = &(*temp)->link) {}
    *temp = (NodePtr) malloc(sizeof(NodeType));
    (*temp)->stud = s;
    (*temp)->link = NULL;
    return true;
}

bool deleteItem(HashTable *ht, Student s) {
    NodePtr *trav, temp;
    for (trav = ht->elem + getHash(s); *trav; trav = &(ht->elem[getHash(s)]->link)) {
        if ((*trav)->stud.studID == s.studID & !strcmp((*trav)->stud.studName, s.studName)) {
            temp = *trav;
            *trav = (*trav)->link;
            free(temp);
            return true;
        }
    }
    return false;
}

void visualiseTable(HashTable ht) {
    int i;
    NodePtr trav;
    for (i = 0; i < 20; i++) {
        printf("Row %d:", i + 1);
        for (trav = ht.elem[i]; trav; trav = trav->link) {
            printf(" %d", trav->stud.studID);
        }
        printf("\n\n");
    }
}

void freeHash(HashTable *ht) {
    NodePtr temp;
    for (int i = 0; i < 20; i++) {
        while (ht->elem[i] != NULL) {
            temp = ht->elem[i];
            ht->elem[i] = ht->elem[i]->link;
            free(temp);
        }
    }
}