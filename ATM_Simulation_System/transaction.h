
#ifndef ATM_SIMULATION_SYSTEM_TRANSACTION_H
#define ATM_SIMULATION_SYSTEM_TRANSACTION_H

struct Transaction
{
    int accountNumber;
    char transactionType[20];
    double amount;
    double balanceAfter;
};

void depositMoney(int accountNumber);
void withdrawMoney(int accountNumber);
void transactionHistory(int accountNumber);

#endif // ATM_SIMULATION_SYSTEM_TRANSACTION_H
