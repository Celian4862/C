#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef MAX
#define MAX 5
#endif

#ifndef MAX_CHAR
#define MAX_CHAR 20
#endif

struct temp
{
	char fname[MAX_CHAR];	
	char lname[MAX_CHAR];	
	char program[MAX_CHAR];
	int age;
};

struct info
{
	struct temp var[MAX];
};

struct temp *sortByProgramAsc(struct temp *var);
struct info sortByLastNameAsc(struct temp *var);
void printThisOne(struct temp *var);
void printThisTwo(struct info var);

int main(int argc, char *argv[]) {
	struct temp var[MAX] = {
		{"Chris","Evans","BSCPE",51},
		{"John","Doe","BSIT",30},
		{"asdf","qwer","BSCS",19},
		{"wert","sdfg","BSIT",20},
		{"sdfg","hdfgh","BSCS",30}
	};
	struct temp *var2 = sortByProgramAsc(var);
	printThisOne(var2);
	
	printf("\n");				  
						  
	struct info var3 = sortByLastNameAsc(var);	
	printThisTwo(var3);	

	free(var2);
	
	if (argc == 3)
		printf("\n%s %s\n", argv[1], argv[2]);

	return 0;
}

struct temp *sortByProgramAsc(struct temp *var) {
	int index;
	struct temp tempo, *returned = (struct temp*) malloc (sizeof(struct temp) * MAX);
	for (int i = 0; i < MAX; i++) {
		returned[i] = var[i];
	}
	for (int i = 0; i < MAX - 1; i++) {
		index = i;
		for (int j = i + 1; j < MAX; j++) {
			if (strcmp(returned[index].program, returned[j].program) > 0) {
				index = j;
			} else if (strcmp(returned[index].program, returned[j].program) == 0) {
				if (strcmp(returned[index].lname, returned[j].lname) > 0) {
					index = j;
				}
			}
		}
		tempo = returned[index];
		returned[index] = returned[i];
		returned[i] = tempo;
	}
	return returned;
}

struct info sortByLastNameAsc(struct temp *var) {
	int index;
	struct temp tempo;
	struct info returned;
	for (int i = 0; i < MAX; i++) {
		returned.var[i] = var[i];
	}
	for (int i = 0; i < MAX; i++) {
		index = i;
		for (int j = i; j < MAX; j++) {
			if (strcmp(returned.var[index].lname, returned.var[j].lname) > 0) {
				index = j;
			}
		}
		tempo = returned.var[index];
		returned.var[index] = returned.var[i];
		returned.var[i] = tempo;
	}
	return returned;
}

void printThisOne(struct temp *var) {
	for (int i = 0; i < MAX; i++) {
		printf("%s, %s, %s, %d\n", var[i].fname, var[i].lname, var[i].program, var[i].age);
	}
}

void printThisTwo(struct info var) {
	for (int i = 0; i < MAX; i++) {
		printf("%s, %s, %s, %d\n", var.var[i].fname, var.var[i].lname, var.var[i].program, var.var[i].age);
	}
}

#undef MAX
#undef MAX_CHAR