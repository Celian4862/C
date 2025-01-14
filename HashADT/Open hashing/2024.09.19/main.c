#include <stdio.h>
#include <string.h>
#include "hash.h"

int main(int argc, char *argv[]) {
    HashTable ht;
    initDictionary(&ht);
    Student s = {
        s.studID = 21103130,
        s.year = 2
    };
    strcpy(s.studName, "Kurt Kaw");
    strcpy(s.program, "BSCS");
    insert(&ht, s);
    visualiseTable(ht);
    s.studID = 21103131;
    strcpy(s.studName, "Kura Kwa");
    strcpy(s.program, "BSCS");
    s.year = 1;
    insert(&ht, s);
    visualiseTable(ht);
    freeHash(&ht);
    return 0;
}