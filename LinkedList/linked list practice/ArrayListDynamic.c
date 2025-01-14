#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ArrayListDynamic.h"

List initList(int size) {
	List list;
	list.elems = (int *) malloc (size * sizeof(int));
	list.count = 0;
	list.max = size;
	return list;
}

void resizeList(List *list, int value) {
	list->elems = (int*) realloc (list->elems, sizeof(int) * value);
	list->max = value;
	if (list->max < list->count) {
		list->count = list->max;
	}
}

void displayList(List list) {
	int i;
	for (i = 0; i < list.count; i++) {
		printf("%d ", list.elems[i]);
	}
	printf("\n");
}

void insertFront(List *list, int value) {
	memmove(list->elems + 1, list->elems, sizeof(int) * list->count);
	list->elems[0] = value;
	list->count++;
}

void insertRear(List *list, int value) {
	list->elems[list->count++] = value;
}

void insertInto(List *list, int value, int position) {
	memmove(list->elems + position + 1, list->elems + position, sizeof(int) * (list->count - position));
	list->elems[position] = value;
	list->count++;
}

void deleteFront(List *list) {
	memmove(list->elems, list->elems + 1, sizeof(int) * (list->count - 1));
	list->count--;
}

void deleteRear(List *list) {
	list->count--;
}

void deleteFrom(List *list, int position) {
	memmove(list->elems + position, list->elems + position + 1, sizeof(int) * (list->count - position));
	list->count--;
}
