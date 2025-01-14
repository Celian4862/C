// Prints a hollow triangle. Will need to review to figure out how to print a solid one.

#include <stdio.h>
#include <stdlib.h>

int main() {
	int height;
	printf("Enter the height of the triangle: ");
	scanf("%d", &height);
	
	int asterisk_count = 1;
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < height - 1 - i; j++) {
			printf(" ");
		}
		for (int j = 0; j < asterisk_count; j++) {
			if (i == height - 1) {
				printf("*");
			}
			else {
				if (j == 0 || j == asterisk_count - 1) {
					printf("*");
				}
				else {
					printf(" ");
				}
			}
		}
		asterisk_count += 2;
		printf("\n");
	}
	
	return 0;
}
