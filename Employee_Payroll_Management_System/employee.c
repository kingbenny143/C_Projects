#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include "employee.h"

void displayEmployee(struct Employee employee) {

    printf("\n========================================================\n");
    printf("                 EMPLOYEE DETAILS\n");
    printf("========================================================\n");

    printf("Employee ID      : %d\n", employee.id);
    printf("Name             : %s\n", employee.name);
    printf("Department       : %s\n", employee.department);
    printf("Designation      : %s\n", employee.designation);
    printf("Phone Number     : %s\n", employee.phone);
    printf("Email Address    : %s\n", employee.email);

    printf("\n---------------- Salary Details ----------------\n");

    printf("Basic Salary     : %.2f\n", employee.basicSalary);
    printf("HRA              : %.2f\n", employee.hra);
    printf("DA               : %.2f\n", employee.da);
    printf("TA               : %.2f\n", employee.ta);
    printf("PF               : %.2f\n", employee.pf);
    printf("Tax              : %.2f\n", employee.tax);
    printf("Gross Salary     : %.2f\n", employee.grossSalary);
    printf("Net Salary       : %.2f\n", employee.netSalary);

    printf("========================================================\n");
}

void addEmployee() {
    int op;
    int valid = 1;

    struct Employee employee;
    struct Employee temp;

    FILE *fin;
    FILE *fout;

    fin = fopen("employees.dat", "rb");
    fout = fopen("employees.dat", "ab");

    if (fin == NULL || fout == NULL) {

        printf("Error opening file.\n");

        if (fin != NULL)
            fclose(fin);

        if (fout != NULL)
            fclose(fout);

        return;
    }

    printf("\n========================================================\n");
    printf("                 ADD EMPLOYEE\n");
    printf("========================================================\n");

    do {

        printf("Enter Employee ID: ");
        scanf("%d", &employee.id);

        if (employee.id <= 0)
            printf("\nEmployee ID must be greater than zero.\n");

    } while (employee.id <= 0);

    while (fread(&temp, sizeof(temp), 1, fin)) {

        if (temp.id == employee.id) {

            printf("\nEmployee ID already exists.\n");

            fclose(fin);
            fclose(fout);

            return;
        }
    }

    rewind(fin);

    while(1) {
        valid = 1;
        printf("Enter Employee Name: ");
        scanf("%49s", employee.name);

        for (int i = 0; employee.name[i] != '\0'; i++) {
            if (!isalpha(employee.name[i])) {
                valid = 0;
                break;
            }
        }
        if (!valid) {
            printf("\nName should contain only alphabets");
            continue;
        }
        break;
    }


    printf("1. IT\n2. HR\n3. Finance\n4. Marketing");
    printf("\nEnter Department: ");
    do{
        scanf("%d", &op);
        if (op < 1 || op > 4)
            printf("\nOption should be between 1 to 4");
    }while (op < 1 || op > 4);

    if (op == 1) {
        strcpy(employee.department,"IT");
    }
    else if (op == 2) {
        strcpy(employee.department,"HR");
    }
    else if (op == 3) {
        strcpy(employee.department,"Finance");
    }
    else if (op == 4) {
        strcpy(employee.department,"Marketing");
    }
    else {
        printf("Invalid option");
        fclose(fin);
        fclose(fout);
        return;
    }

    printf("1. Manager\n2. Developer\n3. Tester\n4. Accountant");
    printf("\nEnter Designation: ");
    do {
        scanf("%d", &op);
        if (op < 1 || op > 4)
            printf("\nOption should be between 1 to 4");
    }while (op < 1 || op > 4);

    if (op == 1) {
        strcpy(employee.designation,"Manager");
    }
    else if (op == 2) {
        strcpy(employee.designation,"Developer");
    }
    else if (op == 3) {
        strcpy(employee.designation,"Tester");
    }
    else if (op == 4) {
        strcpy(employee.designation,"Accountant");
    }
    else {
        printf("Invalid option");
        fclose(fin);
        fclose(fout);
        return;
    }

    while (1) {
        valid = 1;
        printf("Enter Phone Number: ");
        scanf("%14s", employee.phone);
        if (strlen(employee.phone) != 10) {
            printf("\nPhone number must contain exactly 10 digits.\n");
            continue;
        }

        for (int i = 0; employee.phone[i] != '\0'; i++) {
            if (!isdigit(employee.phone[i])) {
                valid = 0;
                break;
            }
        }

        if (!valid) {
            printf("\nPhone number should contain only digits.\n");
            continue;
        }
        break;
    }
    while (fread(&temp, sizeof(temp), 1, fin)) {
        if (strcmp(temp.phone,employee.phone) == 0) {
            printf("\nPhone Number already exists.\n");
            fclose(fin);
            fclose(fout);
            return;
        }
    }

    rewind(fin);

    printf("Enter your email address: ");
    scanf("%49s", employee.email);

    while (strchr(employee.email, '@') == NULL || strchr(employee.email, '.') == NULL) {
        printf("Enter a valid email address: ");
        scanf("%49s", employee.email);
           }

    while (fread(&temp, sizeof(temp), 1, fin)) {
        if (strcmp(temp.email, employee.email) == 0) {
            printf("nEmail address already exists.\n");
            fclose(fin);
            fclose(fout);
            return;
        }
    }

    rewind(fin);

    do {
        printf("Enter Basic Salary (₹): ");
        scanf("%f", &employee.basicSalary);

        if (employee.basicSalary <= 0)
            printf("\nEmployee Salary should be greater than 0.\n");

    } while (employee.basicSalary <= 0);

    employee.hra = 0.0;
    employee.da = 0.0;
    employee.ta = 0.0;
    employee.pf = 0.0;
    employee.tax = 0.0;
    employee.grossSalary = 0.0;
    employee.netSalary = 0.0;

    fwrite(&employee, sizeof(employee), 1, fout);

    fclose(fin);
    fclose(fout);

    printf("\nEmployee added successfully!\n");

}

void viewEmployee() {
    int id, found = 0;

    FILE *fin;

    struct Employee employee;

    fin = fopen("employees.dat", "rb");

    if (fin == NULL) {
        printf("\nEmployee file does not exist.\n");
        return;
    }

    do {
        printf("Enter Employee Id: ");
        scanf("%d", &id);

        if (id <= 0)
            printf("Employee ID must be greater than 0.\n");
    }while (id <= 0);

    while (fread(&employee, sizeof(employee), 1, fin)) {
        if (employee.id == id) {
            found = 1;
            displayEmployee(employee);
            break;
        }
    }
    if (!found)
        printf("\nEmployee Id does not exist.\n");

    fclose(fin);
}

void searchEmployee() {
    FILE *fin;

    struct Employee employee;

    int found = 0, choice, id, valid;
    char name[50], phone[15];

    fin = fopen("employees.dat", "rb");

    if (fin == NULL) {
        printf("\nEmployee file does not exist.\n");
        return;
    }

    while (1) {

        printf("\n==============================\n");
        printf("      SEARCH EMPLOYEE\n");
        printf("==============================\n");
        printf("1. Search by Employee ID\n");
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
                    printf("\nEnter Employee ID: ");
                    scanf("%d", &id);

                    if (id <= 0)
                        printf("Employee ID must be greater than zero.\n");

                } while (id <= 0);

                while (fread(&employee, sizeof(employee), 1, fin)) {

                    if (employee.id == id) {
                        found = 1;
                        displayEmployee(employee);
                        break;
                    }
                }

                if (!found)
                    printf("\nEmployee ID does not exist.\n");

                break;

            case 2:
                rewind(fin);
                found = 0;

                while (1) {

                    valid = 1;

                    printf("Enter Employee Name: ");
                    scanf("%49s", name);

                    for (int i = 0; name[i] != '\0'; i++) {

                        if (!isalpha(name[i])) {
                            valid = 0;
                            break;
                        }
                    }

                    if (!valid) {
                        printf("Employee name should contain only alphabets.\n");
                        continue;
                    }

                    break;
                }

                while (fread(&employee, sizeof(employee), 1, fin)) {

                    if (strcmp(employee.name, name) == 0) {
                        found = 1;
                        displayEmployee(employee);
                        break;
                    }
                }

                if (!found)
                    printf("\nEmployee Name does not exist.\n");

                break;

            case 3:
                rewind(fin);
                found = 0;

                while (1) {

                    valid = 1;

                    printf("Enter Phone Number: ");
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

                    break;
                }

                while (fread(&employee, sizeof(employee), 1, fin)) {

                    if (strcmp(employee.phone, phone) == 0) {
                        found = 1;
                        displayEmployee(employee);
                        break;
                    }
                }

                if (!found)
                    printf("\nPhone number does not exist.\n");

                break;

            case 4:
                printf("\nReturning to Main Menu...\n");
                fclose(fin);
                return;

            default:
                printf("\nInvalid Choice.\n");
        }
    }
}

void updateEmployee() {
    struct Employee employee, temp;

    FILE *fin;
    FILE *fout;
    FILE *fcheck;

    int id;
    int found = 0;
    int choice;
    int valid;
    int op;

    fin = fopen("employees.dat", "rb");
    fout = fopen("temp.dat", "wb");

    if (fin == NULL || fout == NULL) {
        printf("\nEmployee file does not exist.\n");
        return;
    }

    do {
        printf("Enter Employee ID: ");
        scanf("%d", &id);

        if (id <= 0)
            printf("\nEmployee ID must be greater than 0.\n");

    } while (id <= 0);

    while (fread(&employee, sizeof(employee), 1, fin)) {

        if (employee.id == id) {

            found = 1;

            printf("\n==============================");
            printf("\n      UPDATE EMPLOYEE");
            printf("\n==============================");
            printf("\n1. Employee Name");
            printf("\n2. Department");
            printf("\n3. Designation");
            printf("\n4. Phone Number");
            printf("\n5. Email Address");
            printf("\n6. Basic Salary");
            printf("\n7. Exit");
            printf("\nEnter your choice: ");
            scanf("%d", &choice);

            switch (choice) {

            case 1:

                while (1) {

                    valid = 1;

                    printf("Enter Employee Name: ");
                    scanf("%49s", employee.name);

                    for (int i = 0; employee.name[i] != '\0'; i++) {

                        if (!isalpha((unsigned char)employee.name[i])) {
                            valid = 0;
                            break;
                        }
                    }

                    if (!valid) {
                        printf("\nName should contain only alphabets.\n");
                        continue;
                    }

                    break;
                }

                break;

            case 2:

                printf("1. IT\n2. HR\n3. Finance\n4. Marketing\n");

                do {

                    printf("Enter Department: ");
                    scanf("%d", &op);

                    if (op < 1 || op > 4)
                        printf("\nOption should be between 1 and 4.\n");

                } while (op < 1 || op > 4);

                if (op == 1)
                    strcpy(employee.department, "IT");
                else if (op == 2)
                    strcpy(employee.department, "HR");
                else if (op == 3)
                    strcpy(employee.department, "Finance");
                else
                    strcpy(employee.department, "Marketing");

                break;

            case 3:

                printf("1. Manager\n2. Developer\n3. Tester\n4. Accountant\n");

                do {

                    printf("Enter Designation: ");
                    scanf("%d", &op);

                    if (op < 1 || op > 4)
                        printf("\nOption should be between 1 and 4.\n");

                } while (op < 1 || op > 4);

                if (op == 1)
                    strcpy(employee.designation, "Manager");
                else if (op == 2)
                    strcpy(employee.designation, "Developer");
                else if (op == 3)
                    strcpy(employee.designation, "Tester");
                else
                    strcpy(employee.designation, "Accountant");

                break;

            case 4:

                while (1) {

                    valid = 1;

                    printf("Enter Phone Number: ");
                    scanf("%14s", employee.phone);

                    if (strlen(employee.phone) != 10) {
                        printf("\nPhone number must contain exactly 10 digits.\n");
                        continue;
                    }

                    for (int i = 0; employee.phone[i] != '\0'; i++) {

                        if (!isdigit((unsigned char)employee.phone[i])) {
                            valid = 0;
                            break;
                        }
                    }

                    if (!valid) {
                        printf("\nPhone number should contain only digits.\n");
                        continue;
                    }

                    break;
                }

                fcheck  = fopen("employees.dat", "rb");

                while (fread(&temp, sizeof(temp), 1, fcheck)) {

                    if (temp.id != employee.id &&
                        strcmp(temp.phone, employee.phone) == 0) {

                        printf("\nPhone Number already exists.\n");

                        fclose(fcheck);
                        fclose(fin);
                        fclose(fout);
                        remove("temp.dat");
                        return;
                    }
                }

                fclose(fcheck);

                break;

            case 5:

                printf("Enter Email Address: ");
                scanf("%49s", employee.email);

                while (strchr(employee.email, '@') == NULL ||
                       strchr(employee.email, '.') == NULL) {

                    printf("Enter a valid Email Address: ");
                    scanf("%49s", employee.email);
                }

                fcheck = fopen("employees.dat", "rb");

                while (fread(&temp, sizeof(temp), 1, fcheck)) {

                    if (temp.id != employee.id &&
                        strcmp(temp.email, employee.email) == 0) {

                        printf("\nEmail Address already exists.\n");

                        fclose(fcheck);
                        fclose(fin);
                        fclose(fout);
                        remove("temp.dat");
                        return;
                    }
                }

                fclose(fcheck);

                break;

            case 6:

                do {

                    printf("Enter Basic Salary: ");
                    scanf("%f", &employee.basicSalary);

                    if (employee.basicSalary <= 0)
                        printf("\nBasic Salary must be greater than 0.\n");

                } while (employee.basicSalary <= 0);

                employee.hra = 0;
                employee.da = 0;
                employee.ta = 0;
                employee.pf = 0;
                employee.tax = 0;
                employee.grossSalary = 0;
                employee.netSalary = 0;

                break;

            case 7:

                fclose(fin);
                fclose(fout);
                remove("temp.dat");
                return;

            default:

                printf("\nInvalid Choice.\n");
            }
        }

        /* Write every employee record */
        fwrite(&employee, sizeof(employee), 1, fout);
    }

    fclose(fin);
    fclose(fout);

    if (!found) {

        remove("temp.dat");
        printf("\nEmployee ID not found.\n");
        return;
    }

    remove("employees.dat");

    if (rename("temp.dat", "employees.dat") == 0)
        printf("\nEmployee updated successfully.\n");
    else
        printf("\nError updating employee.\n");
}

void deleteEmployee() {

    struct Employee employee;

    FILE *fin;
    FILE *fout;

    int id, found = 0;
    char op;

    fin = fopen("employees.dat", "rb");
    fout = fopen("temp.dat", "wb");

    if (fin == NULL || fout == NULL) {
        printf("\nEmployee file could not be opened.\n");
        return;
    }

    do {
        printf("Enter Employee ID: ");
        scanf("%d", &id);

        if (id <= 0)
            printf("Employee ID must be greater than 0.\n");

    } while (id <= 0);

    while (fread(&employee, sizeof(employee), 1, fin)) {

        if (employee.id == id) {

            found = 1;

            displayEmployee(employee);

            printf("\nAre you sure you want to delete this employee? (Y/N): ");
            scanf(" %c", &op);

            if (op == 'Y' || op == 'y') {
                printf("\nEmployee deleted successfully.\n");
                continue;
            }
        }

        fwrite(&employee, sizeof(employee), 1, fout);
    }

    fclose(fin);
    fclose(fout);

    if (!found) {

        printf("\nEmployee ID not found.\n");
        remove("temp.dat");
        return;
    }

    remove("employees.dat");

    if (rename("temp.dat", "employees.dat") == 0)
        printf("\nEmployee deleted successfully.\n");
    else
        printf("\nError deleting employee.\n");
}

void calculateSalary() {
    struct Employee employee;

    FILE *fin;
    FILE *fout;

    int id;
    int found = 0;

    fin = fopen("employees.dat", "rb");
    fout = fopen("temp.dat", "wb");

    if (fin == NULL || fout == NULL) {
        printf("\nEmployee file does not exist.\n");
        return;
    }

    do {
        printf("Enter Employee ID: ");
        scanf("%d", &id);
        if (id <= 0)
            printf("Employee ID must be greater than 0.\n");
    }while (id <= 0);

    while (fread(&employee, sizeof(employee), 1, fin)) {
        if (employee.id == id) {
            found = 1;

            // Salary Calculations

            employee.hra = (employee.basicSalary * 20)/100;
            employee.da = (employee.basicSalary * 15)/100;
            employee.ta = (employee.basicSalary * 10)/100;
            employee.pf = (employee.basicSalary * 12)/100;
            employee.tax = (employee.basicSalary * 5)/100;
            employee.grossSalary = employee.basicSalary + employee.hra + employee.da + employee.ta;
            employee.netSalary = employee.grossSalary - employee.pf - employee.tax;

            printf("\n==========================================");
            printf("\n        EMPLOYEE SALARY DETAILS");
            printf("\n==========================================");

            printf("\nBasic Salary  : %.2f", employee.basicSalary);
            printf("\nHRA (20%%)     : %.2f", employee.hra);
            printf("\nDA (15%%)      : %.2f", employee.da);
            printf("\nTA (10%%)      : %.2f", employee.ta);
            printf("\nPF (12%%)      : %.2f", employee.pf);
            printf("\nTax (5%%)      : %.2f", employee.tax);

            printf("\n------------------------------------------");
            printf("\nGross Salary  : %.2f", employee.grossSalary);
            printf("\nNet Salary    : %.2f", employee.netSalary);
            printf("\n==========================================\n");
        }
        fwrite(&employee, sizeof(employee), 1, fout);
    }
    fclose(fin);
    fclose(fout);

    if (!found) {
        remove("temp.dat");
        printf("\nEmployee ID not found.\n");
        return;
    }

    remove("employees.dat");

    if (rename("temp.dat", "employees.dat") == 0)
        printf("\nSalary calculated successfully.\n");
    else
        printf("\nError updating salary.\n");
}

void generatePayslip() {

    struct Employee employee;

    FILE *fin;

    int id;
    int found = 0;

    fin = fopen("employees.dat", "rb");

    if (fin == NULL) {
        printf("\nEmployee file does not exist.\n");
        return;
    }

    do {
        printf("Enter Employee ID: ");
        scanf("%d", &id);

        if (id <= 0)
            printf("Employee ID must be greater than 0.\n");

    } while (id <= 0);

    while (fread(&employee, sizeof(employee), 1, fin)) {

        if (employee.id == id) {

            found = 1;

            printf("\n====================================================");
            printf("\n                EMPLOYEE PAYSLIP");
            printf("\n====================================================");

            printf("\nEmployee ID      : %d", employee.id);
            printf("\nEmployee Name    : %s", employee.name);
            printf("\nDepartment       : %s", employee.department);
            printf("\nDesignation      : %s", employee.designation);
            printf("\nPhone Number     : %s", employee.phone);
            printf("\nEmail Address    : %s", employee.email);

            printf("\n----------------------------------------------------");

            printf("\nBasic Salary     : ₹%.2f", employee.basicSalary);
            printf("\nHRA (20%%)        : ₹%.2f", employee.hra);
            printf("\nDA (15%%)         : ₹%.2f", employee.da);
            printf("\nTA (10%%)         : ₹%.2f", employee.ta);
            printf("\nPF (12%%)         : ₹%.2f", employee.pf);
            printf("\nTax (5%%)         : ₹%.2f", employee.tax);

            printf("\n----------------------------------------------------");

            printf("\nGross Salary     : ₹%.2f", employee.grossSalary);
            printf("\nNet Salary       : ₹%.2f", employee.netSalary);

            printf("\n====================================================\n");

            break;
        }
    }

    fclose(fin);

    if (!found)
        printf("\nEmployee ID not found.\n");
}

void showAllEmployees() {

    struct Employee employee;

    FILE *fin;

    int count = 0;

    fin = fopen("employees.dat", "rb");

    if (fin == NULL) {
        printf("\nEmployee file does not exist.\n");
        return;
    }

    printf("\n============================================================");
    printf("\n                 ALL EMPLOYEE RECORDS");
    printf("\n============================================================\n");

    while (fread(&employee, sizeof(employee), 1, fin)) {

        count++;

        printf("\nEmployee %d", count);
        printf("\n------------------------------------------------------------");

        displayEmployee(employee);

        printf("\n------------------------------------------------------------\n");
    }

    fclose(fin);

    if (count == 0)
        printf("\nNo employee records found.\n");
    else
        printf("\nTotal Employees: %d\n", count);
}