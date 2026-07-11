#ifndef BANKING_MANAGEMENT_SYSTEM_BANK_H
#define BANKING_MANAGEMENT_SYSTEM_BANK_H

struct Account {
    int accountNo;
    char name[50];
    char phone[15];
    char email[50];
    float balance;
    char accountType[20];   // Savings or Current
};

void createAccount();
void viewAccount();
void searchAccount();
void depositMoney();
void withdrawMoney();
void transferMoney();
void updateAccount();
void deleteAccount();
void showAllAccounts();

#endif
