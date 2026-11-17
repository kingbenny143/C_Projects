
#include <stdio.h>
#include "atm.h"
#include "account.h"
#include "transaction.h"

int main(void)
{
    int choice;

    printf("\n");
    printf("=====================================\n");
    printf("       ATM SIMULATION SYSTEM\n");
    printf("=====================================\n");

    do
    {
        printf("\n========== MAIN MENU ==========\n");
        printf("1. Create Account\n");
        printf("2. Login\n");
        printf("3. Exit\n");

        printf("\nEnter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("\nInvalid input! Enter a number.\n");

            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF);

            continue;
        }

        switch (choice)
        {
            case 1:
                createAccount();
                break;

            case 2:
                if (authenticateAccount())
                {
                    atmMenu(currentAccountNumber);
                }
                else
                {
                    printf("\nLogin failed! Please try again.\n");
                }
                break;

            case 3:
                printf("\nThank you for using our ATM!\n");
                printf("Exiting program...\n");
                break;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 3);

    return 0;
}
