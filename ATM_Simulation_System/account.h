
#ifndef ATM_SIMULATION_SYSTEM_ACCOUNT_H
#define ATM_SIMULATION_SYSTEM_ACCOUNT_H

struct Account
{
    int accountNumber;
    char accountHolder[50];
    int pin;
    double balance;
};

// Stores the currently logged-in account number
extern int currentAccountNumber;

// Account operations
void createAccount(void);
void displayAccount(struct Account account);
int authenticateAccount(void);
void checkBalance(int accountNumber);
void changePin(int accountNumber);
void showAccountDetails(int accountNumber);

#endif // ATM_SIMULATION_SYSTEM_ACCOUNT_H
