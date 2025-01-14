#include "hash.h"

int main() {
    Stack s;
    initStack(&s);
    ProdDict pd;
    initDict(&pd, 10);
    Product products[10] = {
        {1, "Product 1", 10, 9.99},
        {2, "Product 2", 5, 19.99},
        {3, "Product 3", 8, 14.99},
        {4, "Product 4", 3, 24.99},
        {5, "Product 5", 12, 4.99},
        {6, "Product 6", 7, 29.99},
        {7, "Product 7", 2, 39.99},
        {8, "Product 8", 9, 11.99},
        {9, "Product 9", 6, 19.99},
        {10, "Product 10", 4, 34.99}
    };

    int i;
    for (i = 0; i < 10; i++) {
        push(&s, products[i]);
    }
    visualiseStack(s);
    if (addDict(&pd, products[0])) {
        visualiseDict(pd);
    }

    Product test_prod = {1, "Product 2", 10, 9.99};

    if (addDict(&pd, test_prod)) {
        visualiseDict(pd);
    }

    stackToDict(&pd, &s);
    visualiseDict(pd);
    if (addDict(&pd, products[9])) {
        visualiseDict(pd);
    }

    return 0;
}