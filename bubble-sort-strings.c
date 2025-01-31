#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

void bubble_sort(char **, int, int);

int main(int argc, char **argv)
{
  if (argc == 1) // Failsafe case if there aren't enough arguments
  {
    printf("Not enough arguments; please enter a file path.\n");
    return 1;
  }
  if (argc > 2) // Failsafe case if there are too many arguments
  {
    printf("Too many arguments; please enter only one file name.\n");
    return 2;
  }

  long file_size,          // Variable to store the file size
      i, j;                // Loop variables
  int character_count = 0, // Variable to store the number of characters in a word
      word_count = 0,      // Store the number of words to allocate space
      word_i = 0;          // Iterator for the array of words
  FILE *fp;                // File pointer
  char **strs,             // Array of words
      *buffer;             // Buffer to store the file contents

  fp = fopen(argv[1], "rb");
  if (fp == NULL)
  {
    printf("Error opening file.\n");
    fclose(fp);
    return 3;
  }

  // Find how large the file is
  fseek(fp, 0L, SEEK_END);
  file_size = ftell(fp);
  fseek(fp, 0L, SEEK_SET);

  buffer = (char *)malloc(sizeof(char) * file_size);

  if (NULL == buffer)
  {
    printf("Memory allocation failed.\n");
    return 4;
  }

  fread(buffer, 1, file_size, fp);
  fclose(fp);

  // Count the number of words in the file.
  // This does not help optimise performance, but it optimises storage.
  for (i = 0; i < file_size; i++)
  {
    if (buffer[i] == '\n')
    {
      continue;
    }
    if (buffer[i] == '\r') // Skip carriage return characters
    {
      word_count++;
    }
    else if (buffer[i] == ' ')
    {
      printf("Please format the file to contain words only separated by newlines.\n");
      free(buffer);
      return 5;
    }
    else if (!isalnum(buffer[i]))
    {
      printf("Please use only numbers and letters in the words.\n");
      free(buffer);
      return 5;
    }
  }

  strs = (char **)malloc(sizeof(char *) * word_count);

  if (strs == NULL)
  {
    printf("Memory allocation failed.\n");
    return 4;
  }

  for (i = 0; i < file_size; i++) // Store the words in the array of strings.
  {
    if (buffer[i] == '\r')
    {
      strs[word_i] = (char *)malloc(sizeof(char) * (character_count + 1));
      if (strs[word_i] == NULL)
      {
        printf("Memory allocation failed.\n");
        // Free previously allocated memory
        for (int j = 0; j < word_i; j++)
        {
          free(strs[j]);
        }
        free(strs);
        free(buffer);
        return 4;
      }

      i -= character_count;
      memcpy(strs[word_i], buffer + i, sizeof(char) * character_count);
      strs[word_i][character_count] = '\0'; // Null-terminate the string
      word_i++;
      i += character_count;
      character_count = 0;
    }
    else if (buffer[i] != '\n')
    {
      character_count++;
    }
  }

  free(buffer);

  printf("\nInitial list of words:\n");
  for (i = 0; i < word_count; i++)
  {
    printf("%s ", strs[i]);
  }
  printf("\n");

  bubble_sort(strs, word_count, character_count);

  printf("\nSorted list of words:\n");
  for (i = 0; i < word_count; i++)
  {
    printf("%s ", strs[i]);
  }
  printf("\n");

  return 0;
}

void bubble_sort(char **a, int n, int character_count)
{
  clock_t start, end;
  double cpu_time_used;
  start = clock();

  int i = n - 1, sorted;
  char *temp = (char *)malloc(sizeof(char) * (character_count + 1));
  do
  {
    sorted = 0;
    int j = n - 1;
    do
    {
      if (strcmp(a[j], a[j - 1]) < 0)
      {
        strcpy(temp, a[j]);
        strcpy(a[j], a[j - 1]);
        strcpy(a[j - 1], temp);
        sorted = 1;
      }
    } while (--j);
  } while (--i && sorted);

  end = clock();
  cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

  printf("\nTime taken: %lf seconds\n", cpu_time_used);
}
