
#include <stdio.h>
#include <string.h>
#include "account.h"
#include "transaction.h"

#define ACCOUNT_FILE "accounts.dat"
#define TRANSACTION_FILE "transactions.dat"

// Update account balance
int updateBalance(int accountNumber, double amount)
{
    struct Account account;
    FILE *fp = fopen(ACCOUNT_FILE, "rb+");

    if (fp == NULL)
    {
        printf("\nUnable to open account file!\n");
        return 0;
    }

    while (fread(&account, sizeof(struct Account), 1, fp) == 1)
    {
        if (account.accountNumber == accountNumber)
        {
            account.balance += amount;

            fseek(fp, -(long)sizeof(struct Account), SEEK_CUR);
            fwrite(&account, sizeof(struct Account), 1, fp);

            fclose(fp);
            return 1;
        }
    }

    fclose(fp);
    return 0;
}

// Save transaction details
void saveTransaction(int accountNumber, const char *type,
                     double amount, double balanceAfter)
{
    struct Transaction transaction;

    transaction.accountNumber = accountNumber;
    strcpy(transaction.transactionType, type);
    transaction.amount = amount;
    transaction.balanceAfter = balanceAfter;

    FILE *fp = fopen(TRANSACTION_FILE, "ab");

    if (fp == NULL)
    {
        printf("\nUnable to save transaction history!\n");
        return;
    }

    fwrite(&transaction, sizeof(struct Transaction), 1, fp);
    fclose(fp);
}

// Get current account balance
double getBalance(int accountNumber)
{
    struct Account account;
    FILE *fp = fopen(ACCOUNT_FILE, "rb");

    if (fp == NULL)
        return -1;

    while (fread(&account, sizeof(struct Account), 1, fp) == 1)
    {
        if (account.accountNumber == accountNumber)
        {
            fclose(fp);
            return account.balance;
        }
    }

    fclose(fp);
    return -1;
}

// Deposit money
void depositMoney(int accountNumber)
{
    double amount;

    printf("\n========== DEPOSIT MONEY ==========\n");
    printf("Enter amount to deposit: ");

    if (scanf("%lf", &amount) != 1 || amount <= 0)
    {
        printf("\nInvalid deposit amount!\n");
        return;
    }

    if (updateBalance(accountNumber, amount))
    {
        double balance = getBalance(accountNumber);

        saveTransaction(accountNumber, "Deposit", amount, balance);

        printf("\nDeposit successful!\n");
        printf("Deposited Amount: %.2lf\n", amount);
        printf("Updated Balance: %.2lf\n", balance);
    }
    else
    {
        printf("\nDeposit failed!\n");
    }
}

// Withdraw money
void withdrawMoney(int accountNumber)
{
    double amount;
    double balance;

    printf("\n========== WITHDRAW MONEY ==========\n");
    printf("Enter amount to withdraw: ");

    if (scanf("%lf", &amount) != 1 || amount <= 0)
    {
        printf("\nInvalid withdrawal amount!\n");
        return;
    }

    balance = getBalance(accountNumber);

    if (balance < 0)
    {
        printf("\nAccount not found!\n");
        return;
    }

    if (amount > balance)
    {
        printf("\nInsufficient balance!\n");
        return;
    }

    if (updateBalance(accountNumber, -amount))
    {
        balance = getBalance(accountNumber);

        saveTransaction(accountNumber, "Withdrawal", amount, balance);

        printf("\nWithdrawal successful!\n");
        printf("Withdrawn Amount: %.2lf\n", amount);
        printf("Remaining Balance: %.2lf\n", balance);
    }
    else
    {
        printf("\nWithdrawal failed!\n");
    }
}

// Display transaction history
void transactionHistory(int accountNumber)
{
    struct Transaction transaction;
    int found = 0;

    FILE *fp = fopen(TRANSACTION_FILE, "rb");

    printf("\n========== TRANSACTION HISTORY ==========\n");

    if (fp == NULL)
    {
        printf("\nNo transaction history found!\n");
        return;
    }

    printf("\n%-15s %-15s %-15s %-15s\n",
           "Type", "Amount", "Balance", "Account");

    printf("------------------------------------------------------------\n");

    while (fread(&transaction, sizeof(struct Transaction), 1, fp) == 1)
    {
        if (transaction.accountNumber == accountNumber)
        {
            printf("%-15s %-15.2lf %-15.2lf %-15d\n",
                   transaction.transactionType,
                   transaction.amount,
                   transaction.balanceAfter,
                   transaction.accountNumber);

            found = 1;
        }
    }

    if (!found)
    {
        printf("\nNo transactions available for this account.\n");
    }

    fclose(fp);
}
