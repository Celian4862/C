typedef struct {
	int *elems;
	int count;
	int max;
} List;

List initList(int);
void resizeList(List*, int);
void displayList(List);
void insertFront(List*, int);
void insertRear(List*, int);
void insertInto(List*, int, int);
void deleteFront(List*);
void deleteRear(List*);
void deleteFrom(List*, int);
