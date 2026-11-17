
#include <stdio.h>
#include "account.h"

#define ACCOUNT_FILE "accounts.dat"

// Stores the currently logged-in account number
int currentAccountNumber = 0;

// Clear remaining input from the keyboard
static void clearInputBuffer(void)
{
    int ch;

    while ((ch = getchar()) != '\n' && ch != EOF);
}

// Find an account using its account number
static int findAccount(int accountNumber, struct Account *account)
{
    FILE *fp = fopen(ACCOUNT_FILE, "rb");

    if (fp == NULL)
        return 0;

    while (fread(account, sizeof(struct Account), 1, fp) == 1)
    {
        if (account->accountNumber == accountNumber)
        {
            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

// Create a new account
void createAccount(void)
{
    struct Account account;
    struct Account temp;

    FILE *fp;

    printf("\n========== CREATE ACCOUNT ==========\n");

    printf("Enter Account Number: ");

    if (scanf("%d", &account.accountNumber) != 1)
    {
        printf("\nInvalid account number!\n");
        clearInputBuffer();
        return;
    }

    if (account.accountNumber <= 0)
    {
        printf("\nAccount number must be positive!\n");
        return;
    }

    // Check for duplicate account number
    fp = fopen(ACCOUNT_FILE, "rb");

    if (fp != NULL)
    {
        while (fread(&temp, sizeof(struct Account), 1, fp) == 1)
        {
            if (temp.accountNumber == account.accountNumber)
            {
                printf("\nAccount number already exists!\n");
                fclose(fp);
                return;
            }
        }

        fclose(fp);
    }

    printf("Enter Account Holder Name: ");

    if (scanf(" %49[^\n]", account.accountHolder) != 1)
    {
        printf("\nInvalid account holder name!\n");
        clearInputBuffer();
        return;
    }

    printf("Create 4-digit PIN: ");

    if (scanf("%d", &account.pin) != 1)
    {
        printf("\nInvalid PIN!\n");
        clearInputBuffer();
        return;
    }

    if (account.pin < 1000 || account.pin > 9999)
    {
        printf("\nPIN must contain exactly 4 digits!\n");
        return;
    }

    account.balance = 0.0;

    fp = fopen(ACCOUNT_FILE, "ab");

    if (fp == NULL)
    {
        printf("\nError opening account file!\n");
        return;
    }

    if (fwrite(&account, sizeof(struct Account), 1, fp) != 1)
    {
        printf("\nError saving account!\n");
        fclose(fp);
        return;
    }

    fclose(fp);

    printf("\nAccount created successfully!\n");
    printf("Account Number: %d\n", account.accountNumber);
    printf("Account Holder: %s\n", account.accountHolder);
    printf("Initial Balance: %.2lf\n", account.balance);
}

// Display account information
void displayAccount(struct Account account)
{
    printf("\n========== ACCOUNT DETAILS ==========\n");

    printf("Account Number : %d\n", account.accountNumber);
    printf("Account Holder : %s\n", account.accountHolder);
    printf("Balance        : %.2lf\n", account.balance);
}

// Authenticate account login
int authenticateAccount(void)
{
    int accountNumber;
    int pin;

    struct Account account;

    FILE *fp = fopen(ACCOUNT_FILE, "rb");

    if (fp == NULL)
    {
        printf("\nNo accounts found! Create an account first.\n");
        return 0;
    }

    printf("\n========== ATM LOGIN ==========\n");

    printf("Enter Account Number: ");

    if (scanf("%d", &accountNumber) != 1)
    {
        printf("\nInvalid account number!\n");
        clearInputBuffer();
        fclose(fp);
        return 0;
    }

    printf("Enter PIN: ");

    if (scanf("%d", &pin) != 1)
    {
        printf("\nInvalid PIN!\n");
        clearInputBuffer();
        fclose(fp);
        return 0;
    }

    while (fread(&account, sizeof(struct Account), 1, fp) == 1)
    {
        if (account.accountNumber == accountNumber &&
            account.pin == pin)
        {
            fclose(fp);

            currentAccountNumber = account.accountNumber;

            printf("\nLogin successful!\n");
            printf("Welcome, %s!\n", account.accountHolder);

            return 1;
        }
    }

    fclose(fp);

    currentAccountNumber = 0;

    printf("\nInvalid Account Number or PIN!\n");

    return 0;
}

// Check account balance
void checkBalance(int accountNumber)
{
    struct Account account;

    printf("\n========== CHECK BALANCE ==========\n");

    if (findAccount(accountNumber, &account))
    {
        printf("Account Holder : %s\n", account.accountHolder);
        printf("Current Balance: %.2lf\n", account.balance);
    }
    else
    {
        printf("\nAccount not found!\n");
    }
}

// Change account PIN
void changePin(int accountNumber)
{
    struct Account account;
    int newPin;
    int confirmPin;

    FILE *fp;

    printf("\n========== CHANGE PIN ==========\n");

    fp = fopen(ACCOUNT_FILE, "rb+");

    if (fp == NULL)
    {
        printf("\nUnable to open account file!\n");
        return;
    }

    while (fread(&account, sizeof(struct Account), 1, fp) == 1)
    {
        if (account.accountNumber == accountNumber)
        {
            printf("Enter New 4-digit PIN: ");

            if (scanf("%d", &newPin) != 1)
            {
                printf("\nInvalid PIN!\n");
                clearInputBuffer();
                fclose(fp);
                return;
            }

            if (newPin < 1000 || newPin > 9999)
            {
                printf("\nPIN must contain exactly 4 digits!\n");
                fclose(fp);
                return;
            }

            printf("Confirm New PIN: ");

            if (scanf("%d", &confirmPin) != 1)
            {
                printf("\nInvalid PIN!\n");
                clearInputBuffer();
                fclose(fp);
                return;
            }

            if (newPin != confirmPin)
            {
                printf("\nPINs do not match!\n");
                fclose(fp);
                return;
            }

            account.pin = newPin;

            fseek(fp, -(long)sizeof(struct Account), SEEK_CUR);

            if (fwrite(&account, sizeof(struct Account), 1, fp) != 1)
            {
                printf("\nError updating PIN!\n");
                fclose(fp);
                return;
            }

            fclose(fp);

            printf("\nPIN changed successfully!\n");
            return;
        }
    }

    fclose(fp);

    printf("\nAccount not found!\n");
}

// Display logged-in account details
void showAccountDetails(int accountNumber)
{
    struct Account account;

    if (findAccount(accountNumber, &account))
    {
        displayAccount(account);
    }
    else
    {
        printf("\nAccount not found!\n");
    }
}
