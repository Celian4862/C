#include <stdio.h>
int main(){
	int i, j, k, l;
	printf("This program prints an inverted right triangle.\n");
	printf("Enter how many asterisks the top line should be.\n");
	scanf("%d",&i);
	for (j = i; j > 0; --j) {
		for (k = i - j; k > 0; --k) {
			printf(" ");
		}
		for (l = j; l > 0; --l) {
			printf("*");
		}
		printf("\n");
	}
    
    return 0;

}