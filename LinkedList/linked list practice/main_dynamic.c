#include <stdio.h>
#include "ArrayListDynamic.c"

int main() {
	int choice, value, position;
	do {
		printf("Input the size of the list: ");
		scanf("%d", &value);
		if (value <= 0) {
			printf("Please input a number greater than 0.\n");
		}
	} while (value <= 0);
	List list = initList(value);
	do {
		printf("List actions:\n 1. Display list\n 2. Insert front\n 3. Insert rear\n 4. Insert into\n 5. Delete front\n 6. Delete rear\n 7. Delete from\n 8. Change list size\n 9. Exit\nEnter here: ");
		scanf("%d", &choice);
		
		switch (choice) {
			case 1:
				displayList(list);
				break;
			case 2:
			case 3:
			case 4:
				if (list.count == list.max) {
					printf("List is full.\n");
					break;
				}
				printf("Enter the value to insert: ");
				scanf("%d", &value);
				switch (choice) {
					case 2:
						insertFront(&list, value);
						break;
					case 3:
						insertRear(&list, value);
						break;
					case 4:
						printf("Enter the position at which you wish to insert (from index 0): ");
						scanf("%d", &position);
						if (position > list.count) {
							printf("Invalid position.\n");
							break;
						}
						insertInto(&list, value, position);
						break;
				}
				break;
			case 5:
			case 6:
			case 7:
				if (list.count == 0) {
					printf("The list is empty.\n");
					break;
				}
				switch (choice) {
					case 5:
						deleteFront(&list);
						break;
					case 6:
						deleteRear(&list);
						break;
					case 7:
						printf("Enter the position at which you wish to delete (from index 0): ");
						scanf("%d", &position);
						if (position > list.count) {
							printf("Invalid position.\n");
							break;
						}
						deleteFrom(&list, position);
						break;
				}
				break;
			case 8:
				printf("Enter the new size of the list: ");
				do {
					scanf("%d", &value);
					if (value <= 0)	{
						printf("Size must be greater than 0.\n");
					}
				} while (value <= 0);
				resizeList(&list, value);
			case 9:
				break;
			default:
				printf("Invalid input.\n");
		}
	} while (choice != 9);
	free(list.elems);
	return 0;
}

