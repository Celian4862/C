#include <stdio.h>
#include <stdlib.h>

int main (void)
{
	system("cls");
    int width, height;
    printf("Enter width of skyscraper: ");
    scanf("%d", &width);
    printf("Enter height of skyscraper: ");
    scanf("%d", &height);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width + 2; j++)
        {
            if (i == 0)
            {
            	if (width % 2 == 0)
                {
                    if (j == (width / 2) || j == (width / 2) + 1)
                    {
                        printf("*");
                    }
                    
                    else
                    {
                        printf(" ");
                    }
                }
                else
                {
                    if (j == (width + 1) / 2)
                    {
                        printf("*");
                    }
                    else
                    {
                        printf(" ");
                    }
                }
            }
            else if (i == height - 1)
            {
                printf("*");
            }
            else
            {
                if (j == 0 || j == width + 1)
                {
                    printf(" ");
                }
                else
                {
                    printf("*");
                }
            }
        }
        printf("\n");
    }
    return 0;
}