#include <stdio.h>
#include <stdbool.h>
#define MAXKEYS 4

typedef struct BTPage
{
  short key_count;                   // number of keys in the page
  char key[MAXKEYS];                 // the actual keys
  struct BTPage *child[MAXKEYS + 1]; // RRNs of children
} BTPage;

BTPage *create_BTPage();
bool delete_BT(BTPage *, char);
void display_BT(BTPage *);
bool insert_BT(BTPage *, char);
bool search_BT(BTPage *, char);

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
      printf("%s\n", (search_BT(root, key) ? "Key found." : "Key not found."));
      break;

    case 2:
      char key;
      printf("Enter the key to be inserted: ");
      scanf(" %c", &key);
      printf("%s\n", (insert_BT(root, key) ? "Inserted key successfully." : "Failed to insert key."));
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
  new_page->key_count = 0;
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

// Returns true if the key is successfully inserted, false otherwise
bool insert_BT(BTPage *page, char key)
{
  int i;
  if (page->key_count == 0)
  {
    page->key[0] = key;
    page->key_count++;
  }
  else
  {
    for (i = 0; i < page->key_count; i++)
    {
      if (key < page->key[i])
      {
        insert_BT(page->child[i], key);
        break;
      }
    }
    if (i == page->key_count)
    {
      insert_BT(page->child[i], key);
    }
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