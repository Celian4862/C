#include <stdio.h>
#include <string.h>

#define MAX 128

void radix_sort(char **, const int);
void counting_sort(char **, const int, const int);

int main(int argc, char **argv)
{
  if (argc == 1)
  {
    printf("Usage: %s <strings...>\n", argv[0]);
    return 1;
  }
  char **words = argv + 1;
  radix_sort(words, argc - 1);
  printf("Result:\n");
  for (int i = 0; i < argc - 1; i++)
  {
    printf("%s ", words[i]);
  }
  printf("\n");
  return 0;
}

// MSD radix sort because we're dealing with arrays
void radix_sort(char **words, const int word_size)
{
  int max_length = strlen(words[0]);
  for (int i = 1; i < word_size; i++)
  {
    if (max_length < strlen(words[i]))
    {
      max_length = strlen(words[i]);
    }
  }
}

void counting_sort(char **words, const int word_size, const int letter)
{
  int countArr[MAX] = {0}, word;
  char *outputArr[word_size];

  for (word = 0; word < word_size; word++)
  {
    countArr[words[word][letter]]++;
  }

  for (word = 0; word < MAX; word++)
  {
    countArr[word] += countArr[word - 1];
  }

  for (word = word_size - 1; word >= 0; word--)
  {
    outputArr[--countArr[words[word][letter]]] = words[word];
  }

  memcpy(words, outputArr, word_size * sizeof(char));
}