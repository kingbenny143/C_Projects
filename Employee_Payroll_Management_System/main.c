#include<stdio.h>
#include <stdlib.h>

#include "employee.h"

int main() {
    int op;

    while (1) {
        printf("\n========================================================\n");
        printf("          EMPLOYEE PAYROLL MANAGEMENT SYSTEM\n");
        printf("========================================================\n");

        printf("\n              EMPLOYEE MANAGEMENT\n");
        printf("--------------------------------------------------------\n");
        printf("1. Add Employee\n");
        printf("2. View Employee\n");
        printf("3. Search Employee\n");
        printf("4. Update Employee\n");
        printf("5. Delete Employee\n");

        printf("\n                    PAYROLL\n");
        printf("--------------------------------------------------------\n");
        printf("6. Calculate Salary\n");
        printf("7. Generate Payslip\n");

        printf("\n                    REPORTS\n");
        printf("--------------------------------------------------------\n");
        printf("8. Show All Employees\n");

        printf("\n                     SYSTEM\n");
        printf("--------------------------------------------------------\n");
        printf("9. Exit\n");

        printf("========================================================\n");
        printf("Enter your choice: ");

        if (scanf("%d", &op) != 1) {
            printf("Invalid input! Please enter a number.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (op) {
            case 1:
                addEmployee();
                break;
            case 2:
                viewEmployee();
                break;
            case 3:
                searchEmployee();
                break;
            case 4:
                updateEmployee();
                break;
            case 5:
                deleteEmployee();
                break;
            case 6:
                calculateSalary();
                break;
            case 7:
                generatePayslip();
                break;
            case 8:
                showAllEmployees();
                break;
            case 9:
                printf("\nThank you for using Employee Payroll Management System!\n");
                exit(0);
            default:
                printf("Invalid choice");
                break;
        }
    }
}
