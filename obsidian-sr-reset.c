#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILE_SIZE 1048576 // 1 MB

void process_file(const char *filepath)
{
  FILE *fp = fopen(filepath, "r");
  if (!fp)
    return;

  char *buffer = malloc(MAX_FILE_SIZE);
  if (!buffer)
  {
    fclose(fp);
    return;
  }

  size_t len = fread(buffer, 1, MAX_FILE_SIZE - 1, fp);
  buffer[len] = '\0';
  fclose(fp);

  char *output = malloc(MAX_FILE_SIZE);
  char *out_ptr = output;
  char *read_ptr = buffer;

  while (*read_ptr)
  {
    if (strncmp(read_ptr, "<!--", 4) == 0)
    {
      char *end = strstr(read_ptr, "-->");
      if (end)
      {
        read_ptr = end + 3;
      }
      else
      {
        break;
      }
    }
    else
    {
      *out_ptr++ = *read_ptr++;
    }
  }
  *out_ptr = '\0';

  fp = fopen(filepath, "w");
  if (fp)
  {
    fwrite(output, 1, strlen(output), fp);
    fclose(fp);
  }

  free(buffer);
  free(output);
}

void process_directory(const char *path)
{
  WIN32_FIND_DATA findData;
  char searchPath[MAX_PATH];
  snprintf(searchPath, MAX_PATH, "%s\\*", path);

  HANDLE hFind = FindFirstFile(searchPath, &findData);
  if (hFind == INVALID_HANDLE_VALUE)
    return;

  do
  {
    if (strcmp(findData.cFileName, ".") == 0 || strcmp(findData.cFileName, "..") == 0)
      continue;

    char fullPath[MAX_PATH];
    snprintf(fullPath, MAX_PATH, "%s\\%s", path, findData.cFileName);

    if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
    {
      process_directory(fullPath); // Recurse into subdirectories
    }
    else
    {
      const char *ext = strrchr(findData.cFileName, '.');
      if (ext && strcmp(ext, ".md") == 0)
      {
        printf("Cleaning: %s\n", fullPath);
        process_file(fullPath);
      }
    }

  } while (FindNextFile(hFind, &findData));
  FindClose(hFind);
}

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    printf("Usage: %s <path_to_vault>\n", argv[0]);
    return 1;
  }

  process_directory(argv[1]);
  return 0;
}
