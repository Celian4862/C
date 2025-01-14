#include "pq.h"

void (*display[])(Heap, int) = {breadth_first, preorder, inorder, postorder};

bool initHeap(Heap *h) {
    h->arr = (int*) malloc (sizeof(int) * (15));
    if (!h->arr) {
        printf("Memory allocation failed.\n");
        return false;
    }
    h->max = 15;
    h->lastIdx = -1;
    h->depth_breadth = 8;
    return true;
}

bool resizeHeap(Heap *h) {
    h->arr = (int*) realloc (h->arr, sizeof(int) * (h->max + h->depth_breadth * 2));
    if (!h->arr) {
        printf("Memory allocation failed.\n");
        return false;
    }
    h->depth_breadth *= 2;
    h->max += h->depth_breadth;
    return true;
}

bool insertHeap(Heap *h, int data) {
    if (h->lastIdx == h->max - 1 && !resizeHeap(h)) {return false;}
    int child = ++h->lastIdx;
    while (data < h->arr[(child - 1) / 2] && child != 0) {
        h->arr[child] = h->arr[(child - 1) / 2];
        child = (child - 1) / 2;
    }
    h->arr[child] = data;
    return true;
}

bool rmHeap(Heap *h) {
    if (h->lastIdx == -1) return false;
    int last = h->arr[h->lastIdx], i, smaller;
    h->arr[h->lastIdx--] = h->arr[0];
    for (
        i = 0,
        smaller = (i * 2 + 2 <= h->lastIdx && h->arr[i * 2 + 2] < h->arr[i * 2 + 1]) ? i * 2 + 2 : i * 2 + 1;

        i * 2 + 1 <= h->lastIdx && last > h->arr[smaller];

        h->arr[i] = h->arr[smaller],
        i = smaller,
        smaller = (i * 2 + 2 <= h->lastIdx && h->arr[i * 2 + 2] < h->arr[i * 2 + 1]) ? i * 2 + 2 : i * 2 + 1
    ) {}

    h->arr[i] = last;
    return true;
}

bool heapify(Heap *h) {
    if (h->lastIdx == -1) return false;
    for (int j = (h->lastIdx - 1) / 2; j >= 0; j--) {
        int temp = h->arr[j],
        smaller = (j * 2 + 2 <= h->lastIdx && h->arr[j * 2 + 1] < h->arr[j * 2 + 2]) ? j * 2 + 1 : j * 2 + 2;

        int i;
        for (
            i = j;

            i * 2 + 1 <= h->lastIdx && temp > h->arr[smaller];

            h->arr[i] = h->arr[smaller],
            i = smaller,
            smaller = (i * 2 + 2 <= h->lastIdx && h->arr[i * 2 + 1] < h->arr[i * 2 + 2]) ? i * 2 + 1 : i * 2 + 2
        ) {}
        h->arr[i] = temp;
    }
    return true;
}

void breadth_first(Heap h, int idx) { // Must pass idx = 0 to display the entire tree
    while (idx <= h.lastIdx) {
        printf("%d ", h.arr[idx++]);
    }
}

void preorder(Heap h, int idx) {
    if (idx <= h.lastIdx) {
        printf("%d ", h.arr[idx]);
        preorder(h, 2 * idx + 1);
        preorder(h, 2 * idx + 2);
    }
}

void inorder(Heap h, int idx) {
    if (idx <= h.lastIdx) {
        inorder(h, 2 * idx + 1);
        printf("%d ", h.arr[idx]);
        inorder(h, 2 * idx + 2);
    }
}

void postorder(Heap h, int idx) {
    if (idx <= h.lastIdx) {
        postorder(h, 2 * idx + 1);
        postorder(h, 2 * idx + 2);
        printf("%d ", h.arr[idx]);
    }
}