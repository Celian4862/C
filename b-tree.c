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

typedef struct QueueNode
{
  BTPage *page;
  struct QueueNode *next;
} QueueNode;

typedef struct Queue
{
  QueueNode *head;
  QueueNode *tail;
} Queue;

BTPage *create_BTPage();
bool delete_BT(BTPage *, char);
void display_BT(BTPage *);
void free_BT(BTPage *);
bool insert_BT(BTPage **, char);
insert_status insert_BT_(BTPage *, char, BTPage **, char *);
bool search_BT(BTPage *, char);
// bool split(BTPage *, char, BTPage *);
bool split(char, BTPage *, BTPage *, char *, BTPage **, BTPage *);

// Queue functions
QueueNode *createQueueNode(BTPage *);
void dequeue(Queue *);
bool enqueue(Queue *, BTPage *);

int main()
{
  short choice = 0;
  char key; // For inserting a new key
  BTPage *root = create_BTPage();

  printf("B-Tree Programme\n");
  while (choice != 5)
  {
    printf("\n");
    printf("1. Search a key in B-Tree\n");
    printf("2. Insert a key in B-Tree\n");
    printf("3. Delete a key in B-Tree\n");
    printf("4. Display B-Tree\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
    scanf(" %hd", &choice);

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
      if (key < 'A' || key > 'Z')
      {
        printf("Invalid key. Please enter an uppercase letter.\n");
      }
      else
      {
        if (insert_BT(&root, key))
        {
          printf("Inserted key successfully.\n");
        }
        else
        {
          printf("Failed to insert key.\n");
        }
      }
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

// Display the B-Tree in level order
// This function uses a queue to traverse the B-Tree level by level
void display_BT(BTPage *root)
{
  if (root == NULL)
  {
    printf("B-Tree is empty.\n");
    return; // If the B-Tree is empty, return
  }
  Queue q;
  q.head = q.tail = NULL; // Initialize the queue
  enqueue(&q, root);      // Enqueue the root page
  while (q.head != NULL)
  {
    BTPage *current_page = q.head->page; // Get the current page from the queue
    dequeue(&q);                         // Dequeue the current page

    // Print the keys in the current page
    printf("[");
    for (int i = 0; i < current_page->key_count; i++)
    {
      printf("%c ", current_page->key[i]);
    }
    printf("] "); // Print the keys in the current page

    // Enqueue all child pages of the current page
    for (int i = 0; i <= current_page->key_count; i++)
    {
      if (current_page->child[i] != NULL)
      {
        enqueue(&q, current_page->child[i]);
      }
    }
  }
  printf("\n"); // Print a newline after displaying the B-Tree
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

bool insert_BT(BTPage **root, char key)
{
  char promo_key = 0;
  BTPage *promo_r_child = NULL; // Pointer to the promoted child page
  if (insert_BT_(*root, key, &promo_r_child, &promo_key) != ERROR)
  {
    if (promo_r_child != NULL)
    {
      // If a new page was created, set it as the new root
      BTPage *new_root = create_BTPage();
      if (new_root == NULL)
      {
        printf("Memory allocation failed.\n");
        return false;
      }
      new_root->key[0] = promo_key;       // Set the promoted key in the new root
      new_root->child[0] = *root;         // Set the old root as the first child of the new root
      new_root->child[1] = promo_r_child; // Set the promoted child as the second child of the new root
      new_root->key_count = 1;            // Update the key count of the new root
      *root = new_root;                   // Update the root pointer to point to the new root
    }
    return true;
  }
  return false;
}

// Returns true if the key is successfully inserted, false otherwise
insert_status insert_BT_(BTPage *page, char key, BTPage **promo_r_child, char *promo_key)
{
  if (page == NULL)
  {
    *promo_r_child = NULL;
    *promo_key = key;
    return PROMOTION;
  }

  int i;
  for (i = 0; i < page->key_count && key > page->key[i]; i++)
  {
    if (page->key[i] == key)
    {
      printf("Duplicate key exists.\n");
      return ERROR;
    }
  }

  BTPage *p_b_rrn = NULL;
  char p_b_key = 0;
  insert_status return_value = insert_BT_(page->child[i], key, &p_b_rrn, &p_b_key);

  if (return_value == NO_PROMOTION || return_value == ERROR)
  {
    return return_value; // No promotion or error occurred
  }
  else if (page->key_count < m - 1)
  {
    // Insert p_b_key and p_b_rrn (promoted from below) into the current page
    for (i = page->key_count - 1; i >= 0 && page->key[i] > p_b_key; i--)
    {
      page->key[i] = page->key[i - 1];     // Shift keys to the right
      page->child[i + 1] = page->child[i]; // Shift child pointers to the right
    }
    page->key[i + 1] = p_b_key;   // Insert the promoted key
    page->child[i + 2] = p_b_rrn; // Insert the promoted child pointer
    page->key_count++;            // Increment the key count
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
    split(p_b_key, p_b_rrn, page, promo_key, promo_r_child, new_page);
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

  // Copy all keys and pointers from PAGE into a working page that can hold one extra key and child.
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
  temp->child[i] = page->child[i]; // Copy the last child pointer to temp

  // Insert I_KEY and I_RRN into their proper places in the working page.
  for (i = temp->key_count - 1; i > 0 && temp->key[i - 1] > i_key; i--)
  {
    temp->key[i] = temp->key[i - 1];     // Shift keys to the right
    temp->child[i + 1] = temp->child[i]; // Shift child pointers to the right
  }
  temp->key[i] = i_key;       // Insert the new key in the correct position
  temp->child[i + 1] = i_rrn; // Insert the new child pointer

  // Allocate and initialise a new page in the B-tree file to hold NEWPAGE.
  if (new_page == NULL)
  {
    printf("Memory allocation failed\n");
    free(temp); // Free the temporary page if memory allocation fails
    return false;
  }

  // Set PROMO_KEY to value of middle key, which will be promoted after the split.
  *promo_key = temp->key[m / 2]; // Set the promoted key to the middle key
  // Set PROMO_R_CHILD to RRN of NEWPAGE.
  *promo_r_child = new_page; // Set the promoted child pointer

  // Copy keys and child pointers preceding PROMO_KEY from the working page to PAGE.
  for (i = 0; i < m / 2; i++)
  {
    page->key[i] = temp->key[i];     // Copy the left half of keys to the original page
    page->child[i] = temp->child[i]; // Copy the left half of child pointers to the original page
  }
  page->child[i] = temp->child[i]; // Copy the last child pointer to the original page
  page->key_count = m / 2;         // Update the key count of the original page

  // Copy keys and child pointers following PROMO_KEY from the working page to NEWPAGE.
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

/**
 *
 * QUEUE FUNCTIONS
 *
 */

QueueNode *createQueueNode(BTPage *page)
{
  QueueNode *new_node = (QueueNode *)malloc(sizeof(QueueNode));
  if (new_node == NULL)
  {
    printf("Queue memory allocation failed\n");
    return NULL;
  }
  new_node->page = page; // Assign the page to the new node
  new_node->next = NULL; // Initialize the next pointer to NULL
  return new_node;
}

void dequeue(Queue *q)
{
  if (q->head == NULL)
  {
    return; // Queue is empty, nothing to dequeue
  }
  QueueNode *temp = q->head; // Store the head node temporarily
  q->head = q->head->next;   // Move the head pointer to the next node
  free(temp);                // Free the old head node
}

bool enqueue(Queue *q, BTPage *page)
{
  QueueNode *new_node = createQueueNode(page); // Create a new queue node
  if (new_node == NULL)
  {
    return false; // Memory allocation failed
  }
  if (q->head == NULL)
  {
    q->head = q->tail = new_node; // If the queue is empty, set the head and the tail to the new node
  }
  else
  {
    q->tail->next = new_node; // Link the new node to the end of the queue
    q->tail = new_node;       // Update the tail pointer to the new node
  }
  return true;
}