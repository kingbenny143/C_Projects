#include <stdio.h>
#include <stdlib.h>
#include "library.h"
#include <string.h>

void addBooks() {
    FILE* fout;
    FILE* fin;

    struct Book book;

    fout = fopen("books.dat","ab");
    fin = fopen("books.dat","rb");

    if(fout==NULL) {
        printf("Error: Unable to open books.dat\n");
        return;
    }
    else {
        struct Book temp;

        printf("Enter the book id: ");
        while(fread(&temp, sizeof(temp), 1, fin)) {
            if (book.id == temp.id) {
                printf("Book with ID %d already exists. Please enter a unique ID.\n", book.id);
                fclose(fin);
                fclose(fout);
                return;
            }
        }
        scanf("%d", &book.id);
        printf("Enter the title: ");
        scanf("%49s", book.title);
        printf("Enter the author: ");
        scanf("%49s", book.author);
        printf("Enter the category: ");
        scanf("%49s", book.category);
        do {
            printf("Enter book quantity: ");
            scanf("%d", &book.quantity);
        } while (book.quantity < 0);
        book.available = book.quantity;

        fwrite(&book, sizeof(book), 1, fout);
    }
    fclose(fout);
    fclose(fin);
    printf("Record saved successfully...!\n\n");
}

void viewBooks() {
    int sid, found = 0;

    FILE* fin;

    struct Book book;
    fin = fopen("books.dat","rb");
    if(fin==NULL) {
        printf("Error: Unable to open books.dat\n");
        return;
    }
    else {
        printf("Enter the book id to view: ");
        scanf("%d", &sid);
        while (fread(&book, sizeof(book), 1, fin)) {
            if(sid == book.id) {
                found = 1;
                printf("==================\n");
                printf("Book id: %d\n", book.id);
                printf("Title: %s\n", book.title);
                printf("Author: %s\n", book.author);
                printf("Category: %s\n", book.category);
                printf("Quantity: %d\n", book.quantity);
                printf("Available: %d\n", book.available);
                printf("==================\n\n");
                break;
            }
        }
    }

    fclose(fin);
    if (!found) {
        printf("Record not found!");
    }
}

void searchBooks() {
    int found = 0;

    FILE* fin;
    
    struct Book book;
    
    fin = fopen("books.dat","rb");
    
    if(fin==NULL) {
        printf("Error: Unable to open books.dat\n");
        return;
    }
    else {
        while (1) {
            int choice, sid;
            printf("\n==================\n");
            printf("   Search Book\n");
            printf("==================\n");
            printf("1.Book ID\n2.Title\n3.Author\n4.Exit\nEnter your choice: ");
            scanf("%d", &choice);

            if (choice == 1) {
                rewind(fin);

                printf("Enter the book id: ");
                scanf("%d", &sid);
                while (fread(&book, sizeof(book), 1, fin)) {
                    if (sid == book.id) {
                        found = 1;
                        printf("==================\n");
                        printf("Book id: %d\n", book.id);
                        printf("Title: %s\n", book.title);
                        printf("Author: %s\n", book.author);
                        printf("Category: %s\n", book.category);
                        printf("Quantity: %d\n", book.quantity);
                        printf("Available: %d\n", book.available);
                        printf("==================\n\n");
                        break;
                    }
                }
                if (!found) {
                    printf("Record with ID %d not found!", sid);
                }
            }
            else if (choice == 2) {
                char title[50];
                found = 0;
                rewind(fin);

                printf("Enter the book title: ");
                scanf("%49s", title);
                while (fread(&book, sizeof(book), 1, fin)) {
                    if (strcmp(book.title, title) == 0) {
                        found = 1;
                        printf("==================\n");
                        printf("Book id: %d\n", book.id);
                        printf("Title: %s\n", book.title);
                        printf("Author: %s\n", book.author);
                        printf("Category: %s\n", book.category);
                        printf("Quantity: %d\n", book.quantity);
                        printf("Available: %d\n", book.available);
                        printf("==================\n\n");
                        break;
                    }
                }
                if (!found) {
                    printf("Record with title %s not found!", title);
                }
            }
            else if (choice == 3) {
                char author[50];
                found = 0;
                rewind(fin);

                printf("Enter the book author: ");
                scanf("%49s", author);
                while (fread(&book, sizeof(book), 1, fin)) {
                    if (strcmp(book.author, author) == 0) {
                        found = 1;
                        printf("==================\n");
                        printf("Book id: %d\n", book.id);
                        printf("Title: %s\n", book.title);
                        printf("Author: %s\n", book.author);
                        printf("Category: %s\n", book.category);
                        printf("Quantity: %d\n", book.quantity);
                        printf("Available: %d\n", book.available);
                        printf("==================\n\n");
                        break;
                    }
                }
                if (!found) {
                    printf("Record with author %s not found!", author);
                }
            }
            else if (choice == 4) {
                break;
            }
            else {
                printf("Invalid choice! Please try again.\n");
            }
        }
    }
    fclose(fin);
}

void updateBookDetails() {
    struct Book book;
    int sid, found = 0, choice;
    
    FILE* fout;
    FILE* fin;

    fout = fopen("books.dat","rb");
    fin = fopen("temp.dat","wb");

    if(fout==NULL || fin==NULL) {
        printf("Error: Unable to open books.dat\n");
        return;
    }
    else {
        printf("Enter the book id to update: ");
        scanf("%d", &sid);

        while (fread(&book, sizeof(book), 1, fout)) {
            if(sid == book.id) {
                found = 1;
                printf("==================\n");
                printf("options to update:\n");
                printf("==================\n");
                printf("1. Title\n2. Author\n3. Category\n4. Quantity\n5. Exit\n");

                printf("Enter your choice: ");
                scanf("%d", &choice);
                switch(choice) {
                    case 1:
                        printf("Enter the new title: ");
                        scanf("%49s", book.title);
                        break;
                    case 2:
                        printf("Enter the new author: ");
                        scanf("%49s", book.author);
                        break;
                    case 3:
                        printf("Enter the new category: ");
                        scanf("%29s", book.category);
                        break;
                    case 4:
                        int issued = book.quantity - book.available;
                        int newQuantity;

                        do {
                            printf("Enter new quantity: ");
                            scanf("%d", &newQuantity);
                        } while (newQuantity < issued);

                        book.quantity = newQuantity;
                        book.available = newQuantity - issued;
                        break;
                    case 5:
                        fclose(fout);
                        fclose(fin);
                        remove("temp.dat");
                        return;
                    default:
                        printf("Invalid choice!\n");
                }
            }
            fwrite(&book, sizeof(book), 1, fin);
        }
    }
    fclose(fout);
    fclose(fin);
    if (!found) {
        printf("Record with ID %d not found!", sid);
        remove("temp.dat");
    }
    else{
        printf("Record updated successfully...!\n\n");
        remove("books.dat");
        rename("temp.dat", "books.dat");
    }
}

void deleteBooks() {
    FILE* fout;
    FILE* fin;

    int sid, found = 0;

    struct Book book;

    fout = fopen("books.dat","rb");
    fin = fopen("temp.dat","wb");

    if(fout == NULL || fin == NULL) {
        printf("Error: Unable to open books.dat\n");
        return;
    }
    else {
        printf("Enter the book id to delete: ");
        scanf("%d", &sid);

        while (fread(&book, sizeof(book), 1, fout)) {
            if(sid == book.id) {
                found = 1;
                continue;
            }
            fwrite(&book, sizeof(book), 1, fin);
        }
    }
    fclose(fout);
    fclose(fin);
    if (!found) {
        printf("Record with ID %d not found!", sid);
        remove("temp.dat");
    }
    else{
        printf("Record deleted successfully...!\n\n");
        remove("books.dat");
        rename("temp.dat", "books.dat");
    }
}

void issueBooks() {
    FILE* fout;
    int sid, found = 0;
    struct Book book;

    fout = fopen("books.dat","rb+");

    if(fout==NULL) {
        printf("Error: Unable to open books.dat\n");
        return;
    }
    else{
        printf("Enter the book id to issue: ");
        scanf("%d", &sid);
        while(fread(&book, sizeof(book), 1, fout)){
            if(sid == book.id) {
                found = 1;
                if(book.available > 0) {
                    book.available--;
                    fseek(fout, -sizeof(book), SEEK_CUR);
                    fwrite(&book, sizeof(book), 1, fout);
                    printf("Book issued successfully...!\n\n");
                }
                else {
                    printf("Sorry, the book is not available...\n\n");
                }
                break;
            }
        }
        if(!found) {
            printf("Record with ID %d not found!", sid);
        }
    }
    fclose(fout);

}

void returnBooks() {
    FILE* fout;
    struct Book book;
    int sid, found = 0;

    fout = fopen("books.dat","rb+");
    if(fout==NULL) {
        printf("Error: Unable to open books.dat\n");
        return;
    }
    else{
        printf("Enter the book id to return: ");
        scanf("%d", &sid);
        while(fread(&book, sizeof(book), 1, fout)){
            if(sid == book.id) {
                if(book.available < book.quantity) {
                    found = 1;
                    book.available++;
                    fseek(fout, -sizeof(book), SEEK_CUR);
                    fwrite(&book, sizeof(book), 1, fout);
                    printf("Book returned successfully...!\n\n");
                    break;
                }
            }
            if(!found) {
                printf("Record with ID %d not found!", sid);
            }
        }
        fclose(fout);
    }
}               