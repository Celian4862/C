#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hash.h"

// STACK OPERATIONS

void initStack(Stack *s) {
    *s = NULL;
}

bool isEmpty(Stack s) {
    return !s;
}

bool push(Stack *s, Product p) {
    NodePtr temp = (NodePtr) malloc (sizeof(NodeType));
    if (temp == NULL) {
        return false;
    }
    temp->prod = p;
    temp->link = *s;
    *s = temp;
    return true;
}

bool pop(Stack *s) {
    if (isEmpty(*s)) {
        return false;
    }
    NodePtr temp = *s;
    *s = (*s)->link;
    free(temp);
    return true;
}

Product peek(Stack s) {
    return s->prod;
}

void visualiseStack(Stack s) {
    printf("%-14s %-17s %-20s %-13s\n", "Product ID", "Product Name", "Product Quantity", "Product Price");
    while (s) {
        printf("%-14d %-17s %-20d %-13.2f\n", s->prod.prodID, s->prod.prodName, s->prod.prodQty, s->prod.prodPrice);
        s = s->link;
    }
}

// HASH TABLE OPERATIONS

void initDict(ProdDict *pd, int max) {
    pd->data = (NodePtr*) malloc (sizeof(NodePtr) * max);
    int i;
    pd->count = 0;
    pd->max = max;
    for (i = 0; i < pd->max; i++) {
        pd->data[i] = NULL;
    }
}

int getHash(int prodID, char *prodName, int max) {
    int hash = prodID, i;
    for (i = 0; i < 5; i++) {
        hash += (int) prodName[i];
    }
    return hash % max;
}

Product getDict(ProdDict pd, int prodID, char *prodName) {
    NodePtr trav;
    for (trav = pd.data[getHash(prodID, prodName, pd.max)]; trav; trav = trav->link) {
        if (prodID == trav->prod.prodID && !strcmp(prodName, trav->prod.prodName)) {
            return trav->prod;
        }
    }
    Product p;
    p.prodID = -1;
    return p;
}

bool addDict(ProdDict *pd, Product p) {
    int hash = getHash(p.prodID, p.prodName, pd->max);
    // Check amount of non-null values in array of linked lists
    if ((int) (pd->max * 0.7) == pd->count && !pd->data[hash]) {
        return false;
    }

    NodePtr *trav, temp;
    bool flag = false; // True if hash index is null
    if (!pd->data[hash]) {
        flag = true; // When hash index is null
    }

    for (trav = pd->data + hash; *trav; trav = &(*trav)->link) {
        if ((*trav)->prod.prodID == p.prodID && !strcmp((*trav)->prod.prodName, p.prodName)) {
            (*trav)->prod.prodQty += p.prodQty;
            return true;
        } else if ((*trav)->prod.prodID > p.prodID || (*trav)->prod.prodID == p.prodID && strcmp((*trav)->prod.prodName, p.prodName) > 0) {
            break;
        }
    }
    temp = (NodePtr) malloc (sizeof(NodeType));
    if (!temp) {
        return false;
    }
    temp->prod = p;
    temp->link = *trav;
    *trav = temp;

    if (flag) {
        pd->count++;
    }

    return true;
}

bool removeDict(ProdDict *pd, int prodID, char *prodName) {
    int hash = getHash(prodID, prodName, pd->max);

    if (!pd->data[hash]) {
        return false;
    }

    NodePtr *trav, temp;

    for (trav = pd->data + hash; *trav && (prodID == (*trav)->prod.prodID && !strcmp(prodName, (*trav)->prod.prodName)); trav = &(*trav)->link) {}
    temp = *trav;
    *trav = (*trav)->link;
    free(temp);
    if (!pd->data[hash]) {
        pd->count--;
    }
    return true;
}

void visualiseDict(ProdDict pd) {
    int i;
    NodePtr trav;
    printf("%-8s %-14s %-17s %-20s %-13s\n", "Hash", "Product ID", "Product Name", "Product Quantity", "Product Price");
    for (i = 0; i < pd.max; i++) {
        printf("%-8d", i);
        if (pd.data[i]) {
            printf(" %-14d %-17s %-20d %-13.2f", pd.data[i]->prod.prodID, pd.data[i]->prod.prodName, pd.data[i]->prod.prodQty, pd.data[i]->prod.prodPrice);
            // Subsequent items in the hash
            for (trav = pd.data[i]->link; trav; trav = trav->link) {
                printf("\n%-8s %-14d %-17s %-20d %-13.2f", "", trav->prod.prodID, trav->prod.prodName, trav->prod.prodQty, trav->prod.prodPrice);
            }
        }
        printf("\n");
    }
}

void stackToDict(ProdDict *pd, Stack *s) {
    NodePtr temp;
    while (*s) {
        addDict(pd, (*s)->prod);
        temp = *s;
        *s = (*s)->link;
        free(temp);
    }
}