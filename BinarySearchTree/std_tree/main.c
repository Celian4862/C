#include "bst.h"

int main(int argc, char **argv) {
    BST tree;
    init(&tree);
    int arr[] = {15, 10, 5, 13, 20};
    for (int i = 0; i < sizeof(arr) / 4; i++) {
        insert(&tree, arr[i]);
    }
    allDisplay(tree);
    return 0;
}