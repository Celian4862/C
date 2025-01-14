#ifndef SET_OPERATIONS_H
#define SET_OPERATIONS_H

#include <stdbool.h>

typedef struct {
    int *elems; // Values: present - 1, absent - 0
    int count;
    int max;
} Set;

// typedef char Set;

Set createSet(int max);
void initSet(Set *s, int max);

bool addElement(Set *s, int item);
bool removeElement(Set *s, int item);
void displaySet(Set s);
bool isElement(Set s, int item);
bool isSubset(Set a, Set b);

Set unionSet(Set a, Set b);
Set intersectionSet(Set a, Set b);
Set differenceSet(Set a, Set b);
Set symmetricDifferenceSet(Set a, Set b);
void freeSet(Set *s);

#endif