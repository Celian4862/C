#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char String[30];

typedef struct {
	String fname;
	char mi;
	String lname;
} Name;

int main() {
	Name a, b;
	strcpy(a.fname, "Peter");
	a.mi = 'A';
	strcpy(a.lname, "Griffin");
	memcpy(&b, &a, sizeof(Name));
	printf("%s %c %s\n", a.fname, a.mi, a.lname);
	printf("%s %c %s\n", b.fname, b.mi, b.lname);
	return 0;
}
