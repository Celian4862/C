#include <stdio.h>
#include "ArrayListStatic.c"

int main() {
	int choice, value, position;
	List list = createList();
	do {
		printf("List actions:\n 1. Display list\n 2. Insert front\n 3. Insert rear\n 4. Insert into\n 5. Delete front\n 6. Delete rear\n 7. Delete from\n 8. Exit\nEnter here: ");
		scanf("%d", &choice);
		
		switch (choice) {
			case 1:
				displayList(list);
				break;
			case 2:
			case 3:
			case 4:
				if (list.count == MAX) {
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
			default:
				printf("Invalid input.\n");
		}
	} while (choice != 8);
	return 0;
}
