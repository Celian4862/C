#include <stdio.h>
#define MAX 10

typedef int LabelAdjMat[MAX][MAX];

typedef struct {
  int u,v, weight;
} vertex;

typedef struct {
  vertex edge[MAX - 1];
  int lastNdx;
} EdgeList;

typedef struct {
  EdgeList el;
  int cost;
} MST;

MST Prims(LabelAdjMat, vertex);

int main(int argc, char **argv) {
  return 0;
}

MST Prims(LabelAdjMat A, vertex startV) {

}