/**
 * Note: when using this programme, please ensure
 * the following:
 * - The file contains words separated by newlines.
 * - The words contain only letters and numbers.
 * - The file does not contain any spaces.
 * - The last word in the file has only one empty
 *   line after it; no more, no less.
 */

/*
Test case (copy to a file, including the last empty line):
azure
ashen
brown
crowd
apple
clean
burnt
blast
cream
chase
light
arise
alien
alert
alter

 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define ASCII_SIZE 128

int radix_sort(char **, int);

/**
 * Return codes:
 * 0: Success
 * 1: Not enough arguments
 * 2: Too many arguments
 * 3: Error opening file
 * 4: Memory allocation failed
 * 5: File format error
 */
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

  // Find the size of the longest word
  for (i = 0; i < word_count; i++)
  {
    if (strlen(strs[i]) > character_count) // No need to reinitialise character_count because it was set to 0 in the previous loop
    {
      character_count = strlen(strs[i]);
    }
  }

  // Resize all of strs to the size of the longest word
  for (i = 0; i < word_count; i++)
  {
    strs[i] = (char *)realloc(strs[i], sizeof(char) * (character_count + 1));
    if (strs[i] == NULL)
    {
      printf("Memory allocation failed.\n");
      // Free previously allocated memory
      for (int j = 0; j < word_count; j++)
      {
        free(strs[j]);
      }
      free(strs);
      free(buffer);
      return 4;
    }

    // Pad each string with null characters
    for (j = strlen(strs[i]); j < character_count; j++)
    {
      strs[i][j] = '\0';
    }
  }

  printf("\nInitial list of words:\n");
  for (i = 0; i < word_count; i++)
  {
    printf("%s ", strs[i]);
  }
  printf("\n");

  if (radix_sort(strs, word_count))
  {
    printf("Memory allocation failed.\n");
    // Free all dynamically allocated memory
    free(buffer);
    for (i = 0; i < word_count; i++)
    {
      free(strs[i]);
    }
    free(strs);
    return 2;
  }

  printf("\nSorted list of words:\n");
  for (i = 0; i < word_count; i++)
  {
    printf("%s ", strs[i]);
  }
  printf("\n");

  // Free all dynamically allocated memory
  free(buffer);
  for (i = 0; i < word_count; i++)
  {
    free(strs[i]);
  }
  free(strs);

  return 0;
}

/**
 * Sorts an array of strings using the radix sort algorithm.
 * Returns 0 if successful, 1 if memory allocation fails.
 */
int radix_sort(char **strs, int size)
{
  char **buckets[ASCII_SIZE]; // Array of buckets to store the words
  int i,                      // Iterator for the words
      j,                      // Iterator for the buckets
      k;                      // Iterator for the characters in the words

  for (i = 0; i < ASCII_SIZE; i++) // Allocate memory for each bucket
  {
    buckets[i] = (char **)malloc(sizeof(char *) * size);
    if (buckets[i] == NULL)
    {
      // Free previously allocated memory
      for (j = 0; j < i; j++)
      {
        free(buckets[j]);
      }
      return 1;
    }
    for (j = 0; j < size; j++) // Allocate memory for the strings inside the buckets
    {
      buckets[i][j] = (char *)malloc(sizeof(char) * (strlen(strs[j]) + 1));
      if (buckets[i][j] == NULL)
      {
        // Free previously allocated memory
        for (k = 0; k < i; k++)
        {
          for (j = 0; j < size; j++)
          {
            free(buckets[k][j]);
          }
          free(buckets[k]);
        }
        return 1;
      }
    }
  }

  for (i = 0; i < ASCII_SIZE; i++)
  {
    free(buckets[i]);
  }

  return 0;
}