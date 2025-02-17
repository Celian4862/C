#include <stdio.h>

#define MAX 128

void counting_sort(char **, const int, const int, const int);

int main(int argc, char **argv)
{
  if (argc == 1)
  {
    printf("Usage: %s <strings...>\n", argv[0]);
    return 1;
  }
  return 0;
}

void counting_sort(char **arr, const int words, const int word, const int divisor)
{
  int countArr[MAX] = {0}, i;
  char *outputArr[words];

  for (i = 0; i < words; i++)
  {
    countArr[(arr[i][word] / divisor) % 10]++;
  }

  for (i = 0; i < MAX; i++)
  {
    countArr[i] += countArr[i - 1];
  }

  for (i = words - 1; i >= 0; i--)
  {
    outputArr[--countArr[(arr[i][word] / divisor) % 10]] = arr[i];
  }

  memcpy(arr, outputArr, words * sizeof(char));
}