#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "set_operations.h"

Set createSet(int max) {
    Set s;
    s.elems = (int *) calloc (max, sizeof(int));
    s.count = 0;
    s.max = max;
    return s;
}

void initSet(Set *s, int max) {
    s->elems = (int *) calloc (max, sizeof(int));
    s->count = 0;
    s->max = max;
}

bool addElement(Set *s, int item) {
    if (item >= 0 && item < s->max && s->elems[item] == 0) {
        s->elems[item] = 1;
        s->count++;
        return true;
    }
    return false;
}

bool removeElement(Set *s, int item) {
    if (item >= 0 && item < s->max && s->elems[item] == 1) {
        s->elems[item] = 0;
        s->count--;
        return true;
    }
    return false;
}

void displaySet(Set s) {
    int i;
    printf("{ ");
    for (i = 0; i < s.max; i++) {
        if (s.elems[i] == 1) {
            printf("%d ", i);
        }
    }
    printf("}\n");
}

bool isElement(Set s, int item) {
    if (item >= 0 && item < s.max) {
        return (s.elems[item] == 1);
    }
    return false;
}

bool isSubset(Set a, Set b) {
    int max = (a.max < b.max) ? a.max : b.max;
    int i;
    for (i = 0; i < max; i++) {
        if (b.elems[i] && b.elems[i] != a.elems[i]) {
            return false;
        }
    }
    return true;
}

Set unionSet(Set a, Set b) {
    Set bigger_set = (a.max > b.max) ? a : b;
    Set new_set = createSet(bigger_set.max);
    int i, max = (a.max < b.max) ? a.max : b.max;
    for (i = 0; i < max; i++) {
        new_set.elems[i] = a.elems[i] || b.elems[i];
    }
    while (i < bigger_set.max) {
        new_set.elems[i] = bigger_set.elems[i];
    }
    return new_set;
}

Set intersectionSet (Set a, Set b) {
    Set new_set = createSet((a.max > b.max) ? a.max : b.max);
    int i, max = (a.max < b.max) ? a.max : b.max;
    for (i = 0; i < max; i++) {
        new_set.elems[i] = a.elems[i] && b.elems[i];
    }
    return new_set;
}

Set differenceSet(Set a, Set b) {
    Set new_set = createSet((a.max > b.max) ? a.max : b.max);
    int i, max = (a.max < b.max) ? a.max : b.max;
    for (i = 0; i < max; i++) {
        new_set.elems[i] = a.elems[i] && !b.elems[i];
    }
    return new_set;
}

Set symmetricDifferenceSet(Set a, Set b) {
    Set bigger_set = (a.max > b.max) ? a : b;
    Set new_set = createSet(bigger_set.max);
    int i, max = (a.max < b.max) ? a.max : b.max;
    for (i = 0; i < max; i++) {
        new_set.elems[i] = a.elems[i] != b.elems[i];
    }
    for (; i < bigger_set.max; i++) {
        new_set.elems[i] = bigger_set.elems[i];
    }
    return new_set;
}

void freeSet(Set *s) {
    free(s->elems);
    s->count = 0;
    s->max = 0;
}