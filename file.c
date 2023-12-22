#include "header.h"

// Функція введення даних нового контакту
void add_contact(struct Contact contacts[], int* num_contacts)
{
	if (*num_contacts < MAX_CONTACTS)
	{
		struct Contact new_contact;
		printf("\nEnter first name: ");
		scanf_s("%19s", new_contact.first_name, sizeof(new_contact.first_name));
		printf("Enter second name: ");
		scanf_s("%19s", new_contact.second_name, sizeof(new_contact.second_name));
		printf("Enter phone number: ");
		scanf_s("%19s", new_contact.phone_number, sizeof(new_contact.phone_number));
		printf("Enter email: ");
		scanf_s("%19s", new_contact.email, sizeof(new_contact.email));

		FILE* file;
		errno_t err;
		err = fopen_s(&file, "addressbook.txt", "a");// Використовую "a" для доповнення файлу
		if (err == 0) {
			fprintf(file, "\n %d) Name: %s, Surname: %s, Number: %s, Email: %s.\n", *num_contacts + 1, new_contact.first_name, new_contact.second_name, new_contact.phone_number, new_contact.email);
			printf("\nContact was successfully added to file!\n");
			// Записуємо останній доданий контакт у файл
		}
		else {
			// Помилка відкриття файлу
			printf("File opening failed.\n");
		}
		fclose(file);

		contacts[*num_contacts] = new_contact;
		(*num_contacts)++;
	}
	else
	{
		printf("\nSorry, you can't add more contacts!");
	}
}

// Функція для виведення всіх контактів
void display_contacts(struct Contact contacts[], int num_contacts)
{
	if (num_contacts > 0)
	{
		printf("\nAll contact:");
		for (int i = 0; i < num_contacts; i++)
		{
			printf("\n%d) Name: %s, Surname: %s, Number: %s, Email: %s.\n", i+1, contacts[i].first_name, contacts[i].second_name, contacts[i].phone_number, contacts[i].email);

		}
	}
	else
	{
		printf("There are no contacts!");
	}
}

// Функція для виведення всіх контактів з опцією редагування
void display_contacts_with_options(struct Contact contacts[], int num_contacts)
{
	if (num_contacts > 0)
	{
		printf("\nAll contacts:\n");
		for (int i = 0; i < num_contacts; i++)
		{
			printf("%d. Name: %s, Surname: %s, Number: %s, Email: %s.\n", i + 1, contacts[i].first_name, contacts[i].second_name, contacts[i].phone_number, contacts[i].email);
		}

		int choice;
		printf("\nEnter the number of the contact you want to edit (or 0 to exit): ");
		scanf_s("%d", &choice);

		if (choice >= 1 && choice <= num_contacts)
		{
			edit_contact(contacts, num_contacts, choice - 1); // Виклик функції редагування
		}
		else if (choice != 0)
		{
			printf("Invalid contact number.\n");
		}
	}
	else
	{
		printf("There are no contacts!\n");
	}
}


// Функція редагування обраного контакту
void edit_contact(struct Contact contacts[], int num_contacts, int index)
{
	if (index >= 0 && index < num_contacts)
	{
		struct Contact* selected_contact = &contacts[index];
		int field_choice;

		printf("\nEditing contact:\n");
		printf("Name: %s, Surname: %s, Number: %s, Email: %s.\n",
			selected_contact->first_name, selected_contact->second_name,
			selected_contact->phone_number, selected_contact->email);

		printf("\nSelect a field to edit:\n");
		printf("1. First Name\n");
		printf("2. Second Name\n");
		printf("3. Phone Number\n");
		printf("4. Email\n");
		printf("Enter your choice: ");
		scanf_s("%d", &field_choice);

		switch (field_choice)
		{
		case 1:
			printf("Enter new First Name: ");
			scanf_s("%19s", selected_contact->first_name, sizeof(selected_contact->first_name));
			break;
		case 2:
			printf("Enter new Second Name: ");
			scanf_s("%19s", selected_contact->second_name, sizeof(selected_contact->second_name));
			break;
		case 3:
			printf("Enter new Phone Number: ");
			scanf_s("%19s", selected_contact->phone_number, sizeof(selected_contact->phone_number));
			break;
		case 4:
			printf("Enter new Email: ");
			scanf_s("%19s", selected_contact->email, sizeof(selected_contact->email));
			break;
		default:
			printf("Invalid choice.\n");
			break;
		}

		FILE* file;
		errno_t err;
		err = fopen_s(&file, "addressbook.txt", "w");
		if (err == 0)
		{
			for (int i = 0; i < num_contacts; i++)
			{
				fprintf(file, "%d. Name: %s, Surname: %s, Number: %s, Email: %s.\n",
					i + 1, contacts[i].first_name, contacts[i].second_name,
					contacts[i].phone_number, contacts[i].email);
			}
			fclose(file);
		}
		printf("Contact was successfully edited and saved to file!\n");
	}
	else
	{
		printf("Invalid contact index.\n");
	}
}

// Функція для виведення всіх контактів з опцією видалення обраного
void display_contacts_with_deleting(struct Contact contacts[], int* num_contacts)
{
	if (*num_contacts > 0)
	{
		printf("\nAll contacts:\n");
		for (int i = 0; i < *num_contacts; i++)
		{
			printf("%d) Name: %s, Surname: %s, Number: %s, Email: %s.\n", i + 1, contacts[i].first_name, contacts[i].second_name, contacts[i].phone_number, contacts[i].email);
		}

		int choice;
		printf("\nEnter the number of the contact you want to delete (or 0 to exit): ");
		scanf_s("%d", &choice);

		if (choice >= 1 && choice <= *num_contacts)
		{
			delete_contact(contacts, num_contacts, choice - 1); // Виклик функції видалення
		}
		else if (choice != 0)
		{
			printf("Invalid contact number.\n");
		}
	}
	else
	{
		printf("\nThere are no contacts!\n");
	}
}

// Функція видалення обраного контакту
void delete_contact(struct Contact contacts[], int* num_contacts, int index)
{
	if (index >= 0 && index < *num_contacts)
	{
		// Переміщаємо всі контакти після видаленого назад на одну позицію
		for (int i = index; i < *num_contacts - 1; i++)
		{
			contacts[i] = contacts[i + 1];
		}

		(*num_contacts)--;
		printf("Contact was successfully deleted!\n");

		// Збереження оновленого списку контактів у файл
		FILE* file;
		errno_t err;
		err = fopen_s(&file, "addressbook.txt", "w");
		if (err == 0)
		{
			for (int i = 0; i < *num_contacts; i++)
			{
				fprintf(file, "%d) Name: %s, Surname: %s, Number: %s, Email: %s.\n",
					i + 1, contacts[i].first_name, contacts[i].second_name,
					contacts[i].phone_number, contacts[i].email);
			}
			fclose(file);
		}
		else
		{
			printf("File opening failed.\n");
		}
	}
	else
	{
		printf("Invalid contact index.\n");
	}
}
