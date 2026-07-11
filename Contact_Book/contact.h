#ifndef CONTACT_BOOK_CONTACT_H
#define CONTACT_BOOK_CONTACT_H

struct contact {
    int id;
    char name[50];
    char phone[50];
    char email[50];
};

void addContact();
void viewContact();
void updateContact();
void deleteContact();
void showContacts();

#endif
