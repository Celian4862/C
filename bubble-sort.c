#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubble(int *a, int);
int _atoi(char *);

int main(int argc, char **argv)
{
  if (argc == 1) // Failsafe case if there aren't enough arguments
  {
    printf("Not enough arguments; please enter an array of numbers separated by a space.\n");
    return 1;
  }

  int size = argc - 1,                          // Size to avoid repetitive calculations
      *arr = (int *)malloc(sizeof(int) * size), // Integer array to store the numbers
      i, j = 0;                                 // Iterators for loops

  for (i = 1; i < size + 1; i++, j++)
  {
    arr[j] = _atoi(argv[i]); // Convert from string to integer
  }

  bubble(arr, size);

  printf("\nResult: ");
  for (i = 0; i < size; i++) // Display sorted array
  {
    printf("%d ", arr[i]);
  }

  printf("\n");
  return 0;
}

void bubble(int *a, int n)
{
  clock_t start, end;
  double cpu_time_used;
  start = clock();

  int i = n - 1, sorted, temp;
  do
  {
    sorted = 0;
    int j = n - 1;
    do
    {
      if (a[j] < a[j - 1])
      {
        temp = a[j];
        a[j] = a[j - 1];
        a[j - 1] = temp;
        sorted = 1;
      }
    } while (--j);
  } while (--i && sorted);

  end = clock();
  cpu_time_used = (end - start) / CLOCKS_PER_SEC;

  printf("\nTime taken: %lf seconds\n", cpu_time_used);
}

int _atoi(char *arr)
{
  int i,       // Iterate through the string
      buffer,  // Buffer for the calculations later
      res = 0; // Resulting integer

  for (i = 0; arr[i] != '\0'; i++)
  {
    buffer = (int)arr[i] - (int)'0';
    if (buffer >= 0)
    {
      res *= 10;
      res += buffer;
    }
  }
  return res;
}
