#include <stdio.h>

void counting_sort(char **, const int, const int, const int);

int main(int argc, char **argv)
{
  return 0;
}

void counting_sort(char **arr, const int words, const int word, const int divisor)
{
  int countArr[10] = {0}, i;
  char *outputArr[words];

  for (i = 0; i < words; i++)
  {
    countArr[(arr[i][word] / divisor) % 10]++;
  }

  for (i = 0; i < 10; i++)
  {
    countArr[i] += countArr[i - 1];
  }

  for (i = words - 1; i >= 0; i--)
  {
    outputArr[--countArr[(arr[i][word] / divisor) % 10]] = arr[i];
  }

  memcpy(arr, outputArr, words * sizeof(char));
}