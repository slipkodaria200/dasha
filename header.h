#ifndef HEADER_H //Уникнення подвійного включення коду.
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#define MAX_CONTACTS 100

// Структура, представляє контакт
struct Contact {
	char first_name[20];
	char second_name[20];
	char phone_number[20];
	char email[20];
};

void add_contact(struct Contact contacts[], int* num_contacts);
void display_contacts(struct Contact contacts[], int num_contacts);
void display_contacts_with_options(struct Contact contacts[], int num_contacts);
void edit_contact(struct Contact contacts[], int num_contacts, int index);
void delete_contact(struct Contact contacts[], int* num_contacts, int index);
void display_contacts_with_deleting(struct Contact contacts[], int* num_contacts);

#endif
