#include <stdio.h>
#include <string.h>

#define MAX 128

void radix_sort(char **, const int);
void msd_(char **, const int, const int);
void counting_sort(char **, const int, const int);

int main(int argc, char **argv)
{
  if (argc == 1)
  {
    printf("Usage: %s <strings...>\n", argv[0]);
    return 1;
  }
  char **words = argv + 1;

  printf("Input:\n");
  for (int i = 0; i < argc - 1; i++)
  {
    printf("%s ", words[i]);
  }

  radix_sort(words, argc - 1);

  printf("\n\nResult:\n");
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
  msd_(words, word_size, 0);
}

void msd_(char **words, const int word_size, const int letter)
{
  // 1. Base case
  if (word_size <= 1)
  {
    return;
  }
  // 2. Counting sort
  counting_sort(words, word_size, letter);
  // 3. Recursion
  int start = 0;
  for (int i = 1; i < word_size; i++)
  {
    if (words[i][letter] != words[i - 1][letter])
    {
      msd_(words + start, i - start, letter + 1);
      start = i;
    }
  }
  msd_(words + start, word_size - start, letter + 1);
}

void counting_sort(char **words, const int word_size, const int letter)
{
  int countArr[MAX] = {0}, word;
  char *outputArr[word_size];

  for (word = 0; word < word_size; word++)
  {
    (strlen(words[word]) <= letter)
        ? countArr[0]++
        : countArr[words[word][letter]]++;
  }

  for (word = 1; word < MAX; word++)
  {
    countArr[word] += countArr[word - 1];
  }

  for (word = word_size - 1; word >= 0; word--)
  {
    outputArr[(strlen(words[word]) <= letter)
                  ? --countArr[0]
                  : --countArr[words[word][letter]]] = words[word];
  }

  memcpy(words, outputArr, word_size * sizeof(char *));
}