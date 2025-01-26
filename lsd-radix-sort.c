#include <stdio.h>
#include <stdlib.h>
#include <string.h> // Include the string library for memcpy

int _atoi(char *);
int radix_sort(int *, int);

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

  if (!radix_sort(arr, size))
  {
    printf("Memory allocation failed.\n");
    return 2;
  }

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

int radix_sort(int *arr, int size)
{
  int *g = (int *)malloc(sizeof(int) * size), // Array to store the digits with 1 at the significant digit
      *l = (int *)malloc(sizeof(int) * size), // Array to store the digits with 0 at the significant digit
      i,                                      // arr iterator
      j,                                      // Repetitions counter
      ig = 0,                                 // Counter for array g
      il = 0,                                 // counter for array l
      largest = arr[0],                       // Store the largest number in the array
      power_largest = 0,                      // Counter for the repetition loop
      sig_digit = 1;                          // Determines the current focused significant digit in the binary number

  if (NULL == g || NULL == l)
  {
    printf("Memory allocation failed.\n");
    return 0;
  }

  for (i = 1; i < size; i++) // Find the largest number
  {
    if (largest < arr[i])
      largest = arr[i];
  }

  while (largest > 0) // Find power_largest
  {
    largest /= 2;
    power_largest++;
  }

  for (i = 0; i < power_largest; i++) // Repetition loop
  {
    for (j = 0; j < size; j++) // Sorting loop
    {
      if ((arr[j] & sig_digit) == 0)
      {
        l[il++] = arr[j];
      }
      else
      {
        g[ig++] = arr[j];
      }
    }
    memcpy(arr, l, il * 4);      // Copy array of significant digit 0's to the main array
    memcpy(arr + il, g, ig * 4); // Copy array of significant digit 1's to the main array after the significant digit 0's

    sig_digit *= 2; // Move to the next significant digit in the binary number
    ig = il = 0;    // Reset recipient array counters to 0
  }

  // Free the memory allocated for the arrays
  free(g);
  free(l);

  return 1;
}
