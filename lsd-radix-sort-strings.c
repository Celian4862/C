#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
  if (argc == 1) // Failsafe case if there aren't enough arguments
  {
    printf("Not enough arguments; please enter an array of strings separated by a space.\n");
    return 1;
  }
  if (argc > 2) // Failsafe case if there are too many arguments
  {
    printf("Too many arguments; please enter only one file name.\n");
    return 2;
  }

  long file_size,          // Variable to store the file size
      i;                   // Loop variable
  int character_count = 0; // Variable to store the number of characters in a word
  FILE *fp;

  fopen(argv[1], "rb");
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

  char *buffer = (char *)malloc(sizeof(char) * file_size); // Buffer to store the file contents

  /**
   * Currently require a buffer to store each word from the file
   */

  if (NULL == buffer)
  {
    printf("Memory allocation failed.\n");
    return 4;
  }

  fread(buffer, 1, file_size, fp);
  fclose(fp);

  for (i = 0; i < file_size; i++)
  {
    if (buffer[i] == ' ')
    {
      printf("Please format the file to contain words only separated by newlines.\n");
    }
    if (buffer[i] == '\n')
    {
      i -= character_count;
      memcpy(buffer, buffer + i, character_count);
      i += character_count;
      character_count = 0;
    }
    else
    {
      character_count++;
    }
  }

  free(buffer);

  return 0;
}