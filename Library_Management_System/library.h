#ifndef LIBRARY_MANAGEMENT_SYSTEM_LIBRARY_H
#define LIBRARY_MANAGEMENT_SYSTEM_LIBRARY_H

struct Book {
    int id;
    char title[100];
    char author[50];
    char category[30];
    int quantity;
    int available;
};

void addBooks();
void viewBooks();
void searchBooks();
void updateBookDetails();
void deleteBooks();
void issueBooks();
void returnBooks();

#endif
