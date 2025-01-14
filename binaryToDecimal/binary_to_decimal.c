/*
This code isn't very specific with its inputs; it has been suggested that I instead catch the error of inputting something other than 1 or 0.
*/

#include <stdio.h>
#include <stdlib.h>

void binary_decimal ();
void decimal_binary ();

int main () {
	unsigned int choice;
	do {
	system("cls");
	printf("Binary to decimal: 1\nDecimal to binary: 0\n\nEnter your choice here: ");
	scanf("%u", &choice);
	
	(choice) ? binary_decimal() : decimal_binary();
	
	printf("Again? (1 / 0) ");
	scanf("%u", &choice);
	} while (choice);
}

void binary_decimal() {
	system("cls");
	int binary, decimal = 0, base = 1;
	printf("Enter your binary number: ");
	scanf("%d", &binary);
	
	while (binary > 0) {
		decimal += (binary % 10) * base;
		base *= 2;
		binary /= 10;
	}
	
	printf("Decimal form: %d\n", decimal);
}

void decimal_binary () {
	system("cls");
	int binary = 0, decimal, base = 1;
	printf("Enter your decimal number: ");
	scanf("%d", &decimal);
	
	while (decimal > 0) {
		binary += (decimal % 2) * base;
		base *= 10;
		decimal /= 2;
	}
	printf("Binary form: %d\n", binary);
}