/**
 * Return codes:
 * 0: Success
 * 1: Not enough arguments
 * 2: Too many arguments
 * 3: Error opening file
 * 4: Memory allocation failed
 * 5: File format error
 *
 * Note: when using this programme, please ensure
 * the following:
 * - The file contains words separated by newlines.
 * - The words contain only letters and numbers.
 * - The file does not contain any spaces.
 * - The last word in the file has only one empty
 *   line after it; no more, no less.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int radix_sort(char **, int);

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
      i;                   // Loop variable
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

int radix_sort(char **strs, int size)
{
  char **g = (char **)malloc(sizeof(char *) * size), // Array of greater strings
      **l = (char **)malloc(sizeof(char *) * size);  // Array of lesser strings

  if (g == NULL || l == NULL)
  {
    // Free previously allocated memory
    free(g);
    free(l);
    return 1; // Return value is 1 because it is used as a boolean, not a code
  }

  int i,             // strs iterator
      j,             // Repetitions counter
      k,             // Iterator for returning data to the original array
      ig = 0,        // Counter for array g
      il = 0,        // counter for array l
      sig_digit = 1; // Current focused significant digit

  for (i = 0; i < size; i++)
  {
    g[i] = l[i] = NULL;
  }

  for (i = 0; i < 7; i++)
  {
    for (j = 0; j < size; j++)
    {
      if ((strs[j][0] & sig_digit) == 0)
      {
        l[il] = (char *)realloc(l[il], sizeof(char) * (strlen(strs[j]) + 1));
        if (l[il] == NULL)
        {
          // Free previously allocated memory
          for (int m = 0; m < il; m++)
          {
            free(l[m]);
          }
          for (int m = 0; m < ig; m++)
          {
            free(g[m]);
          }
          free(l);
          free(g);
          return 1; // Return value is 1 because it is used as a boolean, not a code
        }
        strcpy(l[il++], strs[j]);
      }
      else
      {
        g[ig] = (char *)realloc(g[ig], sizeof(char) * (strlen(strs[j]) + 1));
        if (g[ig] == NULL)
        {
          // Free previously allocated memory
          for (int m = 0; m < il; m++)
          {
            free(l[m]);
          }
          for (int m = 0; m < ig; m++)
          {
            free(g[m]);
          }
          free(l);
          free(g);
          return 1; // Return value is 1 because it is used as a boolean, not a code
        }
        strcpy(g[ig++], strs[j]);
      }
    }

    // Place all strings back into the original array
    for (j = 0; j < il; j++)
    {
      strs[j] = (char *)realloc(strs[j], sizeof(char) * (strlen(l[j]) + 1));
      strcpy(strs[j], l[j]);
    }
    k = j;
    for (j = 0; j < ig; j++)
    {
      strs[k] = (char *)realloc(strs[k], sizeof(char) * (strlen(g[j]) + 1));
      strcpy(strs[k++], g[j]);
    }

    sig_digit *= 2; // Move to the next significant digit in the binary number
    ig = il = 0;    // Reset recipient array counters to 0
  }

  for (i = 0; i < size; i++)
  {
    free(l[i]);
    free(g[i]);
  }
  free(l);
  free(g);

  return 0;
}