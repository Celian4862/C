#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
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
  struct BTPage *child[m + 1]; // RRNs of children
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
  short choice = 1;
  char key; // For inserting a new key
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
      printf("Enter the key to be searched: ");
      scanf(" %c", &key);
      printf("%s\n", (search_BT(root, key)) ? "Key found." : "Key not found.");
      break;

    case 2:
      printf("Enter the key to be inserted: ");
      scanf(" %c", &key);
      printf("%s\n", ((insert_BT(root, key, NULL, NULL) != ERROR) ? "Inserted key successfully." : "Failed to insert key."));
      break;

    case 3:
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
  free_BT(root); // Free the B-Tree memory
  return 0;
}

BTPage *create_BTPage()
{
  BTPage *new_page = (BTPage *)malloc(sizeof(BTPage));
  if (new_page == NULL)
  {
    printf("Memory allocation failed\n");
  }
  else
  {
    int i;
    new_page->key_count = 0;
    for (i = 0; i < m - 1; i++)
    {
      new_page->key[i] = '\0';   // Initialize keys to null character
      new_page->child[i] = NULL; // Initialize child pointers to NULL
    }
    new_page->child[i] = NULL; // Initialize the last child pointer to NULL
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

void free_BT(BTPage *page)
{
  if (page == NULL)
  {
    return; // Base case: if the page is NULL, do nothing
  }
  for (int i = 0; i <= page->key_count; i++)
  {
    if (page->child[i] != NULL)
    {
      free_BT(page->child[i]); // Recursively free child pages
    }
  }
  free(page); // Free the current page after all children are freed
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
      printf("Duplicate key exists.\n");
      return ERROR;
    }
  }

  BTPage *p_b_rrn = NULL;
  char *p_b_key = NULL;
  insert_status return_value = insert_BT(page->child[i], key, &p_b_rrn, p_b_key);

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
    BTPage *new_page = create_BTPage();
    if (new_page == NULL)
    {
      printf("Memory allocation failed\n");
      return ERROR; // Memory allocation failed
    }
    split(*p_b_key, p_b_rrn, page, promo_key, promo_r_child, new_page);
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
    page = page->child[i];
  }
  return false; // Key not found
}

bool split(char i_key, BTPage *i_rrn, BTPage *page, char *promo_key, BTPage **promo_r_child, BTPage *new_page)
{
  int i;

  /**
   *
   * Copy all keys and pointers from PAGE into a working page that can hold one extra key and child.
   *
   */
  // Create a temporary page to hold the split keys and children
  BTTemp *temp = (BTTemp *)malloc(sizeof(BTTemp));
  if (temp == NULL)
  {
    printf("Memory allocation failed\n");
    return false;
  }
  temp->key_count = m; // Increase key count by 1 for the new key
  for (i = 0; i < m; i++)
  {
    temp->key[i] = '\0';   // Initialize keys to null character
    temp->child[i] = NULL; // Initialize child pointers to NULL
  }
  temp->child[m] = NULL; // Initialize the last child pointer to NULL

  for (i = 0; i < page->key_count; i++)
  {
    temp->key[i] = page->key[i];     // Copy keys to temp
    temp->child[i] = page->child[i]; // Copy child pointers to temp
  }

  /**
   *
   * Insert I_KEY and I_RRN into their proper places in the working page.
   *
   */
  for (i = temp->key_count - 1; i > 0 && temp->key[i - 1] > i_key; i--)
  {
    temp->key[i] = temp->key[i - 1];     // Shift keys to the right
    temp->child[i + 1] = temp->child[i]; // Shift child pointers to the right
  }
  temp->key[i] = i_key;       // Insert the new key in the correct position
  temp->child[i + 1] = i_rrn; // Insert the new child pointer

  /**
   *
   * Allocate and initialise a new page in the B-tree file to hold NEWPAGE.
   *
   */
  if (new_page == NULL)
  {
    printf("Memory allocation failed\n");
    free(temp); // Free the temporary page if memory allocation fails
    return false;
  }

  /**
   *
   * Set PROMO_KEY to value of middle key, which will be promoted after the split.
   *
   */
  *promo_key = temp->key[m / 2]; // Set the promoted key to the middle key
  /**
   * Set PROMO_R_CHILD to RRN of NEWPAGE.
   */
  *promo_r_child = new_page; // Set the promoted child pointer

  /**
   *
   * Copy keys and child pointers preceding PROMO_KEY from the working page to PAGE.
   *
   */
  for (i = 0; i < m / 2; i++)
  {
    page->key[i] = temp->key[i];     // Copy the left half of keys to the original page
    page->child[i] = temp->child[i]; // Copy the left half of child pointers to the original page
  }
  page->child[i] = temp->child[i]; // Copy the last child pointer to the original page
  page->key_count = m / 2;         // Update the key count of the original page

  /**
   *
   * Copy keys and child pointers following PROMO_KEY from the working page to NEWPAGE.
   *
   */
  for (i = m / 2 + 1; i < m + 1; i++)
  {
    new_page->key[i - (m / 2 + 1)] = temp->key[i];     // Copy the right half of keys to the new page
    new_page->child[i - (m / 2 + 1)] = temp->child[i]; // Copy the right half of child pointers to the new page
  }
  new_page->child[i - (m / 2 + 1)] = temp->child[i]; // Copy the last child pointer to the new page
  new_page->key_count = m - (m / 2 + 1);             // Update the key count of the new page

  free(temp);  // Free the temporary page after copying the keys and pointers
  return true; // End procedure
}