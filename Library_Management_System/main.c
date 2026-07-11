#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "library.h"

int main() {
    int choice;

    while (1) {
        printf("\n==============================\n");
        printf("  LIBRARY MANAGEMENT SYSTEM\n");
        printf("==============================\n");
        printf("1. Add Book\n2. View Books\n3. Search Book\n4. Update Book\n5. Delete Book\n6. Issue Book\n7. Return Book\n8. Exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBooks();
                break;
            case 2:
                viewBooks();
                break;
            case 3:
                searchBooks();
                break;
            case 4:
                updateBookDetails();
                break;
            case 5:
                deleteBooks();
                break;
            case 6:
                issueBooks();
                break;
            case 7:
                returnBooks();
                break;
            case 8:
                exit(0);
            default:
                printf("Please enter a valid choice\n");
        }
    }
    return 0;
}