
#include <stdio.h>
#include "atm.h"
#include "account.h"
#include "transaction.h"

// Display ATM menu
void displayMenu(void)
{
    printf("\n");
    printf("====================================\n");
    printf("             ATM MENU\n");
    printf("====================================\n");
    printf("1. Check Balance\n");
    printf("2. Deposit Money\n");
    printf("3. Withdraw Money\n");
    printf("4. Change PIN\n");
    printf("5. Transaction History\n");
    printf("6. Account Details\n");
    printf("7. Logout\n");
    printf("====================================\n");
    printf("Enter your choice: ");
}

// ATM operations after successful login
void atmMenu(int accountNumber)
{
    int choice;

    do
    {
        displayMenu();

        if (scanf("%d", &choice) != 1)
        {
            int ch;

            if (feof(stdin))
                break;

            printf("\nInvalid input! Enter a number.\n");

            while ((ch = getchar()) != '\n' && ch != EOF);

            continue;
        }

        switch (choice)
        {
            case 1:
                checkBalance(accountNumber);
                break;

            case 2:
                depositMoney(accountNumber);
                break;

            case 3:
                withdrawMoney(accountNumber);
                break;

            case 4:
                changePin(accountNumber);
                break;

            case 5:
                transactionHistory(accountNumber);
                break;

            case 6:
                showAccountDetails(accountNumber);
                break;

            case 7:
                printf("\nLogging out...\n");
                printf("Thank you for using our ATM!\n");
                break;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 7);
}
