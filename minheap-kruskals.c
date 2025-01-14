#include <stdio.h>
#define MAX 10

typedef int LabelAdjMat[MAX][MAX];

typedef struct {
  int u,v,weight;
} Edge;

typedef struct {
  Edge edge[((MAX - 1) * (MAX)) / 2]; // Used arithmetic sum to minimise the amount of storage used
  int lastNdx;
} EdgeList, HeapEdgeList;

typedef struct {
  EdgeList el;
  int cost;
} MST;

MST Kruskals(LabelAdjMat);
EdgeList createMinHeap(LabelAdjMat);
void insertHeap(HeapEdgeList*, Edge);
void rmHeap(HeapEdgeList*);

int main(int argc, char **argv) {
  // Create the matrix
  LabelAdjMat matrix;
  int weight;
  for (int i = 0; i < MAX; i++) {
    for (int j = i + 1; j < MAX; j++) {
      printf("Enter weight for edge %d to %d (-1 for infinity): ", i, j);
      scanf("%d", &weight);
      matrix[i][j] = weight;
    }
  }
  return 0;
}

MST Kruskals (LabelAdjMat A) {

}

HeapEdgeList createMinHeap(LabelAdjMat A) {
  HeapEdgeList el;
  for (int i = 0; i < MAX; i++) {
    for (int j = i + 1; j < MAX; j++) {
      Edge e = {i, j, A[i][j]};
      insertHeap(&el, e);
    }
  }
  return el;
}

void insertHeap(HeapEdgeList *el, Edge e) {
  int child, parent;
  for (
    child = ++el->lastNdx, parent = (child - 1) / 2;

    e.weight < el->edge[parent].weight && child > 0;

    el->edge[parent] = el->edge[child],
    child = parent,
    parent = (child - 1) / 2
  ) {}
  el->edge[child] = e;
}

void rmHeap(HeapEdgeList *el) {

}