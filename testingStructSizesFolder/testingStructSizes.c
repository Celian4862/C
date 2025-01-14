#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
} ptr;

int main(void) {
    ptr *p = (ptr *) malloc (sizeof(ptr));
    p->x = 10;
    printf("%d\n", p->x);
    printf("%lu %lu\n", sizeof(ptr), sizeof(p));
    return 0;
}