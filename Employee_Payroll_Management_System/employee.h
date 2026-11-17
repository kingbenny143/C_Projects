#ifndef EMPLOYEE_PAYROLL_MANAGEMENT_SYSTEM_EMPLOYEE_H
#define EMPLOYEE_PAYROLL_MANAGEMENT_SYSTEM_EMPLOYEE_H

struct Employee {
    int id;

    char name[50];
    char department[30];
    char designation[30];
    char phone[15];
    char email[50];

    float basicSalary;

    float hra;
    float da;
    float ta;
    float pf;
    float tax;

    float grossSalary;
    float netSalary;
};

/* Employee Management */
void addEmployee();
void viewEmployee();
void searchEmployee();
void updateEmployee();
void deleteEmployee();

/* Payroll */
void calculateSalary();
void generatePayslip();

/* Reports */
void showAllEmployees();

/* Helper Function */
void displayEmployee(struct Employee employee);

#endif