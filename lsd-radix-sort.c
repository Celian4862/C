#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Include the string library for memcpy

int _atoi(char *);
void radix_sort(int *, const int);
void counting_sort(int *, const int, const int);

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

  radix_sort(arr, size);

  printf("\nResult: ");
  for (i = 0; i < size; i++) // Display sorted array
  {
    printf("%d ", arr[i]);
  }

  printf("\n");

  return 0;
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

void radix_sort(int *arr, const int size)
{
  int max = arr[0], i, divisor = 1;

  for (i = 0; i < size; i++)
  {
    if (max < arr[i])
    {
      max = arr[i];
    }
  }

  max *= 10;
  while ((max /= 10) != 0)
  {
    counting_sort(arr, size, divisor);
    divisor *= 10;
  }
}

void counting_sort(int *arr, const int size, const int divisor)
{
  int countArr[10] = {0}, outputArr[size], i;

  for (i = 0; i < size; i++)
  {
    countArr[(arr[i] / divisor) % 10]++;
  }

  // Get cumulative / prefix sum
  for (i = 1; i < 10; i++)
  {
    countArr[i] += countArr[i - 1];
  }

  for (i = size - 1; i >= 0; i--)
  {
    outputArr[--countArr[(arr[i] / divisor) % 10]] = arr[i];
  }

  memcpy(arr, outputArr, size * sizeof(int));
}
