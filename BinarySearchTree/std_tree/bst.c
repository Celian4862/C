#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

void (*display[4]) (BST) = {breadth_first, preorder, inorder, postorder};

void init(BST *tree) {
    *tree = NULL;
}

bool insert(BST *tree, int data) {
    BST *trav = tree;
    while (*trav) {
        trav = (data < (*trav)->data) ? &(*trav)->left : &(*trav)->right;
    }
    BST temp = (BST) malloc (sizeof(BST));
    temp->left = temp->right = NULL;
    if (!temp) {
        return false;
    }
    temp->data = data;
    *trav = temp;
    return true;
}

void breadth_first(BST node) {
    QueueADT q = (QueueADT) malloc (sizeof(QueueADT));
    q->head = q->tail = (QueuePtr) malloc (sizeof(QueueNode));
    if (!q->head) {
        printf("Memory allocation failed.");
        return;
    }
    q->tail->node = node;
    q->tail->link = NULL;
    while (q->head) {
        printf("%d ", q->head->node->data);

        QueuePtr temp;

        if (q->head->node->left) {
            // Create new queue elements
            temp = (QueuePtr) malloc (sizeof(QueueNode));

            // Let temp's node point to the next child
            temp->node = q->head->node->left;
            temp->link = NULL;

            // Let tail and then its link point to the next element
            q->tail->link = temp;
            q->tail = temp;
        }
        if (q->head->node->right) {
           temp = (QueuePtr) malloc (sizeof(QueueNode));
           temp->node = q->head->node->right;
           temp->link = NULL;
           q->tail->link = temp;
           q->tail = temp;
        }
        // Let temp point to head
        temp = q->head;
        // Let head move to the next element in the queue
        q->head = q->head->link;
        // Free the node
        free(temp);
    }
    free(q);
}

void preorder(BST node) {
    if (node) {
        printf("%d ", node->data);
        preorder(node->left);
        preorder(node->right);
    }
}

void inorder(BST node) {
    if (node) {
        inorder(node->left);
        printf("%d ", node->data);
        inorder(node->right);
    }
}

void postorder(BST node) {
    if (node) {
        postorder(node->left);
        postorder(node->right);
        printf("%d ", node->data);
    }
}

void allDisplay(BST tree) {
    for (int i = 0; i < 4; i++) {
        display[i](tree);
        printf("\n");
    }
}
