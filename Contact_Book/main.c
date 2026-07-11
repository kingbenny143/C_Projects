#include<stdio.h>
#include <stdlib.h>

#include "contact.h"

int main() {
    int choice;
    while (1) {
        printf("=======Welcome to contact book=======");
        printf("\n1. add contact\n2. view contact\n3. update contact\n4. delete contact\n5.exit\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addContact();
                break;
            case 2:
                viewContact();
                break;
            case 3:
                updateContact();
                break;
            case 4:
                deleteContact();
                break;
            case 5:
                showContacts();
                break;
            case 6:
                exit(0);
                break;
            default:
                printf("Invalid choice");
        }
    }


}