#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<ctype.h>
#include "bank.h"

void displayAccount(struct Account account) {
    printf("\n==================================\n");
    printf("        ACCOUNT DETAILS\n");
    printf("==================================\n");
    printf("Account Number : %d\n", account.accountNo);
    printf("Name           : %s\n", account.name);
    printf("Phone          : %s\n", account.phone);
    printf("Email          : %s\n", account.email);
    printf("Account Type   : %s\n", account.accountType);
    printf("Balance        : %.2f\n", account.balance);
    printf("==================================\n");
}

void createAccount() {
    struct Account account;
    struct Account temp;

    int type;

    FILE *fout;
    FILE *fin;

    fout = fopen("accounts.dat", "ab");
    fin = fopen("accounts.dat", "rb");

    if (fout == NULL || fin == NULL) {
        printf("Error opening file.\n");
        if (fin != NULL) fclose(fin);
        if (fout != NULL) fclose(fout);
        return;
    }

    printf("\n================================\n");
    printf("     Enter your account details\n");
    printf("================================\n");

    do {
        printf("Enter your account number: ");
        scanf("%d", &account.accountNo);

        if (account.accountNo <= 0) {
            printf("Account number must be positive.\n");
        }

    } while (account.accountNo <= 0);

    while (fread(&temp, sizeof(temp), 1, fin)) {
        if (temp.accountNo == account.accountNo) {
            printf("Account number already exists.\n");
            fclose(fin);
            fclose(fout);
            return;
        }
    }

    rewind(fin);

    while (1) {

        int valid = 1;

        printf("Enter your account name: ");
        scanf("%49s", account.name);

        for (int i = 0; account.name[i] != '\0'; i++) {
            if (!isalpha(account.name[i])) {
                valid = 0;
                break;
            }
        }

        if (!valid) {
            printf("Name should contain only alphabets.\n");
            continue;
        }

        break;
    }

    while (1) {

        int valid = 1;

        printf("Enter your phone number: ");
        scanf("%15s", account.phone);

        if (strlen(account.phone) != 10) {
            printf("Phone number must contain exactly 10 digits.\n");
            continue;
        }

        for (int i = 0; account.phone[i] != '\0'; i++) {
            if (!isdigit(account.phone[i])) {
                valid = 0;
                break;
            }
        }

        if (!valid) {
            printf("Phone number should contain only digits.\n");
            continue;
        }

        break;
    }

    while (fread(&temp, sizeof(temp), 1, fin)) {
        if (strcmp(temp.phone, account.phone) == 0) {
            printf("Phone number already exists.\n");
            fclose(fin);
            fclose(fout);
            return;
        }
    }

    rewind(fin);

    printf("Enter your email address: ");
    scanf("%49s", account.email);

    while (strchr(account.email, '@') == NULL ||
           strchr(account.email, '.') == NULL) {

        printf("Enter a valid email address: ");
        scanf("%49s", account.email);
    }

    while (fread(&temp, sizeof(temp), 1, fin)) {
        if (strcmp(temp.email, account.email) == 0) {
            printf("Email address already exists.\n");
            fclose(fin);
            fclose(fout);
            return;
        }
    }

    rewind(fin);

    do {
        printf("Enter initial balance: ");
        scanf("%f", &account.balance);

        if (account.balance < 0) {
            printf("Balance cannot be negative.\n");
        }

    } while (account.balance < 0);

    printf("\n1. Savings\n");
    printf("2. Current\n");
    printf("Select your account type: ");
    scanf("%d", &type);

    if (type == 1) {
        strcpy(account.accountType, "Savings");
    }
    else if (type == 2) {
        strcpy(account.accountType, "Current");
    }
    else {
        printf("Invalid account type.\n");
        fclose(fin);
        fclose(fout);
        return;
    }

    fwrite(&account, sizeof(account), 1, fout);

    fclose(fin);
    fclose(fout);

    printf("\n====================================\n");
    printf("Account created successfully!\n");
    printf("====================================\n");
}

void viewAccount() {
    FILE *fin;
    struct Account account;

    int found = 0;
    int accountNo;

    fin = fopen("accounts.dat", "rb");

    if (fin == NULL) {
        printf("Error: Unable to open accounts.dat\n");
        return;
    }

    do {
        printf("Enter your account number to view: ");
        scanf("%d", &accountNo);

        if (accountNo <= 0) {
            printf("Account number must be positive.\n");
        }

    } while (accountNo <= 0);

    while (fread(&account, sizeof(account), 1, fin)) {
        if (account.accountNo == accountNo) {
            found = 1;
            displayAccount(account);
            break;
        }
    }

    if (!found) {
        printf("Account with account number %d does not exist.\n", accountNo);
    }

    fclose(fin);
}

void searchAccount() {
    FILE *fin;
    struct Account account;

    int found = 0;
    int choice;
    int accountNo;
    char name[50];
    char phone[15];

    fin = fopen("accounts.dat", "rb");

    if (fin == NULL) {
        printf("Error: Unable to open accounts.dat\n");
        return;
    }

    while (1) {

        printf("\n============================\n");
        printf("      SEARCH ACCOUNT\n");
        printf("============================\n");
        printf("1. Search by Account Number\n");
        printf("2. Search by Name\n");
        printf("3. Search by Phone Number\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);

        switch (choice) {

            case 1:

                rewind(fin);
                found = 0;

                do {
                    printf("Enter account number: ");
                    scanf("%d", &accountNo);

                    if (accountNo <= 0) {
                        printf("Account number must be positive.\n");
                    }

                } while (accountNo <= 0);

                while (fread(&account, sizeof(account), 1, fin)) {

                    if (account.accountNo == accountNo) {
                        found = 1;
                        displayAccount(account);
                        break;
                    }
                }

                if (!found) {
                    printf("Account with account number %d does not exist.\n", accountNo);
                }

                break;

            case 2:

                rewind(fin);
                found = 0;

                printf("Enter account name: ");
                scanf("%49s", name);

                while (fread(&account, sizeof(account), 1, fin)) {

                    if (strcmp(account.name, name) == 0) {
                        found = 1;
                        displayAccount(account);
                        break;
                    }
                }

                if (!found) {
                    printf("Account with account name %s does not exist.\n", name);
                }

                break;

            case 3:

                rewind(fin);
                found = 0;

                printf("Enter phone number: ");
                scanf("%14s", phone);

                while (fread(&account, sizeof(account), 1, fin)) {

                    if (strcmp(account.phone, phone) == 0) {
                        found = 1;
                        displayAccount(account);
                        break;
                    }
                }

                if (!found) {
                    printf("Account with phone number %s does not exist.\n", phone);
                }

                break;

            case 4:

                fclose(fin);
                return;

            default:

                printf("Invalid choice. Please try again.\n");
                break;
        }
    }
}

void depositMoney() {
    FILE *fin;
    FILE *fout;

    struct Account account;

    int accountNo;
    float amount;
    int found = 0;
    int updated = 0;
    char op;

    fin = fopen("accounts.dat", "rb");
    fout = fopen("temp.dat", "wb");

    if (fin == NULL || fout == NULL) {
        printf("Error opening file.\n");

        if (fin != NULL) fclose(fin);
        if (fout != NULL) fclose(fout);

        return;
    }

    do {
        printf("Enter account number: ");
        scanf("%d", &accountNo);

        if (accountNo <= 0) {
            printf("Account number must be positive.\n");
        }

    } while (accountNo <= 0);

    do {
        printf("Enter amount to deposit money: ");
        scanf("%f", &amount);

        if (amount <= 0) {
            printf("Deposit amount should be greater than zero.\n");
        }

    } while (amount <= 0);

    while (fread(&account, sizeof(account), 1, fin)) {

        if (account.accountNo == accountNo) {

            found = 1;

            printf("Do you want to add money? (y/n): ");
            scanf(" %c", &op);

            if (op == 'y' || op == 'Y') {

                printf("\nCurrent Balance : %.2f\n", account.balance);
                printf("Deposited Amount: %.2f\n", amount);

                account.balance += amount;
                updated = 1;

                printf("New Balance     : %.2f\n", account.balance);
                printf("\nUpdated Account Details:\n");
                displayAccount(account);

            }
            else {

                printf("Deposit cancelled.\n");

            }
        }

        fwrite(&account, sizeof(account), 1, fout);
    }

    fclose(fin);
    fclose(fout);

    if (!found) {

        printf("Account with account number %d does not exist.\n", accountNo);
        remove("temp.dat");

    }
    else if (updated) {

        remove("accounts.dat");
        rename("temp.dat", "accounts.dat");

        printf("Account record updated successfully.\n");

    }
    else {
        remove("temp.dat");
    }
}

void withdrawMoney() {
    FILE *fin;
    FILE *fout;

    struct Account account;

    int accountNo;
    float amount;
    int found = 0;
    int updated = 0;
    char op;

    fin = fopen("accounts.dat", "rb");
    fout = fopen("temp.dat", "wb");

    if (fin == NULL || fout == NULL) {
        printf("Error opening file.\n");
        if (fin != NULL) fclose(fin);
        if (fout != NULL) fclose(fout);
        return;
    }

    do {
        printf("Enter account number: ");
        scanf("%d", &accountNo);

        if (accountNo <= 0) {
            printf("Account number must be greater than zero.\n");
        }
    }
    while (accountNo <= 0);

    do {
        printf("Enter the amount to withdraw from account: ");
        scanf("%f", &amount);
        if (amount <= 0) {
            printf("Withdrawal amount must be greater than zero.\n");
        }
    }while (amount <= 0);

    while (fread(&account, sizeof(account), 1, fin)) {
       if (account.accountNo == accountNo) {
           found = 1;
           printf("Do you want to withdraw money? (y/n): ");
           scanf(" %c", &op);

           if (op == 'y' || op == 'Y') {

               if (account.balance >= amount ) {
                   printf("\nCurrent Balance : %.2f\n", account.balance);
                   printf("Withdraw Amount : %.2f\n", amount);

                   account.balance -= amount;
                   updated = 1;

                   printf("New Balance     : %.2f\n", account.balance);
                   printf("\nUpdated Account Details:\n");
                   displayAccount(account);
               }
               else {
                   printf("Insufficient balance.\n");
                   printf("Current Balance : %.2f\n", account.balance);
                   printf("Requested Amount: %.2f\n", amount);
               }

           }
           else{
                   printf("Withdraw cancelled.\n");
                   displayAccount(account);
           }
       }
        fwrite(&account, sizeof(account), 1, fout);
    }
    fclose(fin);
    fclose(fout);
    if (!found) {
        printf("Account with account number %d does not exist.\n", accountNo);
        remove("temp.dat");
    }
    else if (updated) {
        remove("accounts.dat");
        rename("temp.dat", "accounts.dat");
        printf("Money withdrawn successfully.\n");
    }
    else {
        remove("temp.dat");
    }
}

void transferMoney(){
    FILE *fin;
    FILE *fout;

    struct Account account;

    int senderAccount;
    int receiverAccount;

    float amount;

    int senderFound = 0;
    int receiverFound = 0;

    char op;

    fin = fopen("accounts.dat", "rb");
    fout = fopen("temp.dat", "wb");

    if (fin == NULL || fout == NULL) {
        printf("Error opening file.\n");
        if (fin != NULL) fclose(fin);
        if (fout != NULL) fclose(fout);
        return;
    }

    do {
        printf("Enter sender account number: ");
        scanf("%d", &senderAccount);
        if (senderAccount <= 0) {
            printf("Account number must be greater than zero.\n");
        }
    }
    while (senderAccount <= 0);

    do {
        printf("Enter receiver account number: ");
        scanf("%d", &receiverAccount);
        if (receiverAccount <= 0) {
            printf("Account number must be greater than zero.\n");
        }
    }
    while (receiverAccount <= 0);

    if (senderAccount != receiverAccount) {
        do {
            printf("Enter transfer money: ");
            scanf("%f", &amount);

            if (amount <= 0) {
                printf("Transfer money must be greater than zero.\n");
            }
        }while (amount <= 0);
    }
    else {
        printf("Sender and receiver account numbers cannot be the same.\n");
        fclose(fin);
        fclose(fout);
        remove("temp.dat");
        return;
    }

    while (fread(&account, sizeof(account), 1, fin)) {

        if (account.accountNo == senderAccount) {
            senderFound = 1;

            if (account.balance < amount) {
                printf("Insufficient balance.\n");
                printf("Current Balance : %.2f\n", account.balance);
                printf("Requested Amount: %.2f\n", amount);

                fclose(fin);
                fclose(fout);
                remove("temp.dat");
                return;
            }
        }

        if (account.accountNo == receiverAccount) {
            receiverFound = 1;
        }
    }

    if (!senderFound) {
        printf("Sender account not found.\n");
        fclose(fin);
        fclose(fout);
        remove("temp.dat");
        return;
    }

    if (!receiverFound) {
        printf("Receiver account not found.\n");
        fclose(fin);
        fclose(fout);
        remove("temp.dat");
        return;
    }

    printf("Confirm transfer? (Y/N): ");
    scanf(" %c", &op);

    if (op != 'y' && op != 'Y') {
        printf("Transfer cancelled.\n");
        fclose(fin);
        fclose(fout);
        remove("temp.dat");
        return;
    }

    rewind(fin);

    while (fread(&account, sizeof(account), 1, fin)) {

        if (account.accountNo == senderAccount) {

            printf("\nSender Account Before Transfer:\n");
            displayAccount(account);

            account.balance -= amount;

            printf("\nSender Account After Transfer:\n");
            displayAccount(account);
        }

        if (account.accountNo == receiverAccount) {

            printf("\nReceiver Account Before Transfer:\n");
            displayAccount(account);

            account.balance += amount;

            printf("\nReceiver Account After Transfer:\n");
            displayAccount(account);
        }

        fwrite(&account, sizeof(account), 1, fout);
    }
    fclose(fin);
    fclose(fout);

    remove("accounts.dat");

    if (rename("temp.dat", "accounts.dat") == 0) {
        printf("\n=====================================\n");
        printf("Transfer completed successfully.\n");
        printf("=====================================\n");
    }
    else {
        printf("Error updating account records.\n");
    }
}

void updateAccount() {
    struct Account account;

    FILE* fin;
    FILE* fout;

    int accountNo, found = 0, op, valid;
    char name[50], phone[15], email[50], type[20];

    fin = fopen("accounts.dat", "rb");
    fout = fopen("temp.dat", "wb");

    if (fin == NULL || fout == NULL) {
        printf("Error opening file.\n");
        if (fin != NULL) fclose(fin);
        if (fout != NULL) fclose(fout);
        return;
    }

    do{
        printf("Enter account number: ");
        scanf("%d", &accountNo);

        if (accountNo <= 0) {
            printf("Account number must be greater than zero.\n");
        }
    }
    while (accountNo <= 0);

    while (fread(&account, sizeof(account),1,fin)) {
        if (accountNo == account.accountNo) {
            found = 1;
            printf("\n===========================\n");
            printf("        UPDATE ACCOUNT      \n");
            printf("===========================\n");
            printf("1. Account Holder Name\n2. Phone Number\n3. Email Address\n4. Account Type\n5. Exit\nEnter your choice: ");
            scanf("%d", &op);
            switch (op) {
                case 1:
                    printf("Previous Name : %s\n", account.name);
                    printf("Enter the name you want to update: ");
                    scanf("%49s", name);
                    strcpy(account.name, name);
                    break;
                case 2:
                    valid = 1;
                    printf("previous phone number: %s\n", account.phone);
                    printf("Enter the phone number you want to update: ");
                    scanf("%14s", phone);
                    if (strlen(phone) != 10) {
                        printf("Phone number must contain exactly 10 digits.\n");
                        continue;
                    }

                    for (int i = 0; phone[i] != '\0'; i++) {
                        if (!isdigit(phone[i])) {
                            valid = 0;
                            break;
                        }
                    }

                    if (!valid) {
                        printf("Phone number should contain only digits.\n");
                        continue;
                    }

                    strcpy(account.phone, phone);
                    break;
                case 3:
                    valid = 1;
                    printf("Previous Email        : %s\n", account.email);
                    printf("Enter the email you want to update: ");
                    scanf("%49s", email);

                    if (!strchr(email, '@') || !strchr(email, '.')) {
                        printf("Enter a valid email");
                        valid = 0;
                    }
                    if (!valid) {
                        printf("Invalid email address.\n");
                        continue;
                    }
                    strcpy(account.email, email);
                    break;
                case 4:
                    printf("Previous Account Type : %s\n", account.accountType);
                    printf("1.Savings\n2.Current\nEnter the account type you want to update: ");
                    scanf("%d", &op);
                    if(op == 1)
                        strcpy(account.accountType, "Savings");
                    else if(op == 2)
                        strcpy(account.accountType, "Current");
                    else
                        printf("Invalid choice");
                    break;
                case 5:
                    fclose(fin);
                    fclose(fout);
                    remove("temp.dat");
                    return;
                default:
                    printf("Invalid choice.\n");
            }
        }
        fwrite(&account, sizeof(account), 1, fout);
    }
    fclose(fin);
    fclose(fout);
    if (!found) {
        printf("Account number not found");
        remove("temp.dat");
    }
    else {
        remove("accounts.dat");

        if (rename("temp.dat", "accounts.dat") == 0) {
            printf("Account updated successfully.\n");
        }
        else {
            printf("Error updating account.\n");
        }
    }
}

void deleteAccount() {
    struct Account account;

    FILE *fin;
    FILE *fout;

    fin = fopen("accounts.dat", "rb");
    fout = fopen("temp.dat", "wb");

    int accountNo, found = 0;
    char ch;

    if (fin == NULL || fout == NULL) {
        printf("Error opening file.\n");
        if (fin != NULL) fclose(fin);
        if (fout != NULL) fclose(fout);
        return;
    }

    do {
        printf("Enter the account number: ");
        scanf("%d", &accountNo);
        if (accountNo <= 0) {
            printf("Account number must be greater than zero.\n");
        }
    }while (accountNo <= 0);

    while (fread(&account, sizeof(account), 1, fin)) {
        if (accountNo == account.accountNo) {
            found = 1;

            printf("Are you sure you want to delete this account? (Y/N): ");
            scanf(" %c", &ch);

            if (ch != 'Y' && ch != 'y') {
                printf("Deletion cancelled.\n");
                fclose(fin);
                fclose(fout);
                remove("temp.dat");
                return;
            }
            continue;
        }
        fwrite(&account, sizeof(account), 1, fout);
    }
    fclose(fin);
    fclose(fout);
    if (!found) {
        printf("Account number not found.\n");
        remove("temp.dat");
    }
    else {
        remove("accounts.dat");

        if (rename("temp.dat", "accounts.dat") == 0) {
            printf("Account deleted successfully.\n");
        }
        else {
            printf("Error deleting account.\n");
        }
    }
}

void showAllAccounts() {
    struct Account account;

    FILE *fin;

    fin = fopen("accounts.dat", "rb");

    if (fin == NULL) {
        printf("Error opening file.\n");
        return;
    }

    if (fread(&account, sizeof(account), 1, fin) == 0) {
        printf("No accounts available.\n");
        fclose(fin);
        return;
    }

    rewind(fin);

    while (fread(&account, sizeof(account), 1, fin)) {
        displayAccount(account);
    }

    fclose(fin);
}