#include <stdbool.h>
#define MAX 10

typedef struct {
	int elems[MAX];
	int count;
} List;

List createList();
void displayList(List);
void insertFront(List*, int);
void insertRear(List*, int);
void insertInto(List*, int, int);
void deleteFront(List*);
void deleteRear(List*);
void deleteFrom(List*, int);
