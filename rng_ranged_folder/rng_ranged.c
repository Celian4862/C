#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main (void)
{
	int min = 1, max = 10;
	char again;
	printf("This is a random number generator, and you can set the range of numbers. Keep in mind that the rand() function is not a very good generator.\n");
	printf("Enter the minimum value:\t");
	scanf("%d", &min);
	/*if (min == NULL)
	{
		printf("Invalid input.");
		return 1;
	}*/
	printf("Enter the maximum value:\t");
	scanf("%d", &max);
	/*if (max == NULL)
	{
		printf("Invalid input.");
		return 1;
	}*/
	srand(time(NULL));
	printf("Your random number is: %d.", (rand() % (max - min + 1)) + min);
	printf("\nAgain? (Y/N) ");
	scanf(" %c", &again);
	if (again == 'y' || again == 'Y')
	{
		main();
	}
	return 0;
}