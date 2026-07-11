#include <stdio.h>
#include <stdlib.h>
#include "bank.h"

int main() {
    int choice;

    while (1) {

        printf("\n========================================================\n");
        printf("             WELCOME TO BANKING MANAGEMENT SYSTEM\n");
        printf("========================================================\n");

        printf("\n               ACCOUNT MANAGEMENT\n");
        printf("--------------------------------------------------------\n");
        printf(" 1. Create Account\n");
        printf(" 2. View Account\n");
        printf(" 3. Search Account\n");
        printf(" 4. Update Account\n");
        printf(" 5. Delete Account\n");

        printf("\n               TRANSACTIONS\n");
        printf("--------------------------------------------------------\n");
        printf(" 6. Deposit Money\n");
        printf(" 7. Withdraw Money\n");
        printf(" 8. Transfer Money\n");

        printf("\n               REPORTS\n");
        printf("--------------------------------------------------------\n");
        printf(" 9. Show All Accounts\n");

        printf("\n               SYSTEM\n");
        printf("--------------------------------------------------------\n");
        printf("10. Exit\n");

        printf("========================================================\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid input! Please enter a number.\n");

            while (getchar() != '\n');   // Clear input buffer
            continue;
        }

        switch (choice) {

            case 1:
                createAccount();
                break;

            case 2:
                viewAccount();
                break;

            case 3:
                searchAccount();
                break;

            case 4:
                updateAccount();
                break;

            case 5:
                deleteAccount();
                break;

            case 6:
                depositMoney();
                break;

            case 7:
                withdrawMoney();
                break;

            case 8:
                transferMoney();
                break;

            case 9:
                showAllAccounts();
                break;

            case 10:
                printf("\n=========================================\n");
                printf(" Thank you for using Banking Management\n");
                printf(" System. Have a great day!\n");
                printf("=========================================\n");
                exit(0);

            default:
                printf("\nInvalid choice! Please try again.\n");
        }
    }

    return 0;
}