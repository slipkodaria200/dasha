#include "header.h"

// Головна функція, вибір запропонованих опцій
int main()
{
	struct Contact contacts[MAX_CONTACTS];
	int num_contacts = 0;
	int choice = 0;

	while (choice != 6)
	{
		printf("\nSelection:\n");
		printf("1. Add contact\n");
		printf("2. Display contacts\n");
		printf("3. Editing contacts\n");
		printf("4. Delete contact\n");
		printf("5. Exit\n");
		printf("\nEnter your choice: ");
		scanf_s("%d", &choice);

		switch (choice)
		{
		case 1:
			add_contact(contacts, &num_contacts);
			break;
		case 2:
			display_contacts(contacts, num_contacts);
			break;
		case 3:
			display_contacts_with_options(contacts, num_contacts);
			break;
		case 4:
			display_contacts_with_deleting(contacts, &num_contacts);
			break;
		case 5:
			printf("Goodbye!\n");
			exit(0);
		default:
			printf("Wrong choice. Try again!\n");
			break;
		}
	}

	return 0;
}