#include <stdio.h>
#include <stdbool.h>
#define m 7

typedef enum insert_status
{
  PROMOTION,
  NO_PROMOTION,
  ERROR
} insert_status;

typedef struct BTPage
{
  short key_count;         // number of keys in the page
  char key[m - 1];         // the actual keys
  struct BTPage *child[m]; // RRNs of children
} BTPage;

typedef struct BTTemp
{
  short key_count;
  char key[m];                 // the actual keys
  struct BTTemp *child[m + 1]; // RRNs of children
} BTTemp;

BTPage *create_BTPage();
bool delete_BT(BTPage *, char);
void display_BT(BTPage *);
void free_BT(BTPage *);
insert_status insert_BT(BTPage *, char, BTPage **, char *);
bool search_BT(BTPage *, char);
// bool split(BTPage *, char, BTPage *);
bool split(char, BTPage *, BTPage *, char *, BTPage **, BTPage *);

int main()
{
  bool choice = 1;
  BTPage *root = create_BTPage();

  printf("B-Tree Programme\n");
  while (choice != 5)
  {
    printf("1. Search a key in B-Tree\n");
    printf("2. Insert a key in B-Tree\n");
    printf("3. Delete a key in B-Tree\n");
    printf("4. Display B-Tree\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
    case 1:
      char key;
      printf("Enter the key to be searched: ");
      scanf(" %c", &key);
      printf("%s\n", (search_BT(root, key)) ? "Key found." : "Key not found.");
      break;

    case 2:
      char key;
      printf("Enter the key to be inserted: ");
      scanf(" %c", &key);
      printf("%s\n", ((insert_BT(root, key, NULL, NULL) != ERROR) ? "Inserted key successfully." : "Failed to insert key."));
      break;

    case 3:
      char key;
      printf("Enter the key to be deleted: ");
      scanf(" %c", &key);
      printf("%s\n", (delete_BT(root, key) ? "Deleted key successfully." : "Failed to delete key."));
      break;

    case 4:
      display_BT(root);
      break;

    case 5:
      printf("Exiting...\n");
      break;

    default:
      printf("Invalid choice\n");
      break;
    }
  }
  return 0;
}

BTPage *create_BTPage()
{
  BTPage *new_page = (BTPage *)malloc(sizeof(BTPage));
  if (new_page == NULL)
  {
    printf("Memory allocation failed\n");
    return NULL;
  }
  new_page->key_count = 0;
  for (int i = 0; i < m; i++)
  {
    new_page->child[i] = NULL; // Initialize child pointers to NULL
  }
  for (int i = 0; i < m - 1; i++)
  {
    new_page->key[i] = '\0'; // Initialize keys to null character
  }
  return new_page;
}

bool delete_BT(BTPage *page, char key)
{
  // Implement the delete operation here
  return false;
}

void display_BT(BTPage *page)
{
  // Implement the display operation here
}

void free(BTPage *page)
{
  if (page == NULL)
  {
    return; // Base case: if the page is NULL, do nothing
  }
  for (int i = 0; i <= page->key_count; i++)
  {
    if (page->child[i] != NULL)
    {
      free_BT(page->child[i]); // Recursively free child pages}
    }
    free(page); // Free the current page
  }
}

// Returns true if the key is successfully inserted, false otherwise
insert_status insert_BT(BTPage *page, char key, BTPage **promo_r_child, char *promo_key)
{
  if (page == NULL)
  {
    *promo_r_child = NULL;
    *promo_key = key;
    return PROMOTION;
  }

  int i;
  for (i = 0; i < page->key_count && key < page->key[i]; i++)
  {
    if (page->key[i] == key)
    {
      return ERROR;
    }
  }

  BTPage *p_b_rrn = NULL;
  char *p_b_key = NULL;
  insert_status return_value = insert(page->child[i], key, &p_b_rrn, p_b_key);

  if (return_value == NO_PROMOTION || return_value == ERROR)
  {
    return return_value; // No promotion or error occurred
  }
  else if (page->key_count < m - 1)
  {
    // Insert p_b_key and p_b_rrn (promoted from below) into the current page
    return NO_PROMOTION;
  }
  else
  {
    split(p_b_key, p_b_rrn, page, promo_key, promo_r_child, NULL);

    return PROMOTION;
  }
}

bool search_BT(BTPage *page, char key)
{
  while (page != NULL)
  {
    int i;
    for (i = 0; i < page->key_count; i++)
    {
      if (key == page->key[i])
      {
        return true; // Key found
      }
      else if (key < page->key[i])
      {
        // Move to the left child of the current key
        page = page->child[i];
        break; // Exit the for loop to process the new page
      }
    }

    // If the key is greater than all keys in the current page
    if (i == page->key_count)
    {
      page = page->child[i]; // Move to the rightmost child
    }
  }
  return false; // Key not found
}

// bool split(BTPage *page, char new_key, BTPage *new_page)
// {
//   BTTemp *temp = (BTTemp *)malloc(sizeof(BTTemp));
//   temp->key_count = page->key_count + 1;
//   int i, j;
//   for (i = 0, j = 0; page->key[i] < new_key; i++, j++)
//   {
//     temp->key[j] = page->key[i]; // Copy keys to temp
//   }
//   temp->key[j++] = new_key; // Insert new key
//   for (; i < page->key_count; i++, j++)
//   {
//     temp->key[j] = page->key[i]; // Copy remaining keys to temp
//   }
//   return false;
// }

bool split(char i_key, BTPage *i_rrn, BTPage *page, char *promo_key, BTPage **promo_r_child, BTPage *new_page)
{
  int i;

  // Create a temporary page to hold the split keys and children
  BTTemp *temp = (BTTemp *)malloc(sizeof(BTTemp));
  temp->key_count = m; // Increase key count by 1 for the new key
  for (i = 0; i < m; i++)
  {
    temp->key[i] = '\0';   // Initialize keys to null character
    temp->child[i] = NULL; // Initialize child pointers to NULL
  }
  temp->child[m] = NULL; // Initialize the last child pointer to NULL

  if (temp == NULL)
  {
    printf("Memory allocation failed\n");
    return false;
  }

  for (i = 0; i < page->key_count; i++)
  {
    temp->key[i] = page->key[i]; // Copy keys to temp
  }
  for (i = temp->key_count - 1; i >= 0; i--)
  {
    if (temp->key[i] > i_key)
    {
      temp->key[i]
    }
  }
}