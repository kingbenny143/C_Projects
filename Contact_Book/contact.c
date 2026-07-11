#include <stdio.h>
#include "contact.h"
#include <ctype.h>
#include <string.h>

void addContact() {
    FILE* fout;
    FILE* fin;
    struct contact con;

    fout = fopen("contact.dat", "ab");
    fin = fopen("contact.dat", "rb");
    if (fout == NULL || fin == NULL) {
        printf("Error opening file.\n");
        if (fin != NULL) fclose(fin);
        if (fout != NULL) fclose(fout);
        return;
    }
    else {
        printf("Enter contact id: ");
        scanf("%d", &con.id);

        struct contact temp;
        int found = 0;

        while (fread(&temp, sizeof(temp), 1, fin)) {
            if (temp.id == con.id) {
                found = 1;
                break;
            }
        }

        rewind(fin);

        if (found) {
            printf("Contact ID already exists.\n");
            fclose(fin);
            fclose(fout);
            return;
        }

        printf("Enter contact name: ");
        scanf("%49s", con.name);

        printf("Enter phone number: ");
        scanf("%49s", con.phone);
        if (strlen(con.phone) != 10) {
            printf("Phone number must contain exactly 10 digits.\n");
            fclose(fin);
            fclose(fout);
            return;
        }

        for (int i = 0; con.phone[i] != '\0'; i++) {

            if (!isdigit(con.phone[i])) {

                printf("Phone number should contain only digits.\n");

                fclose(fin);
                fclose(fout);

                return;
            }
        }

        found = 0;

        while (fread(&temp, sizeof(temp), 1, fin)) {
            if (strcmp(temp.phone, con.phone) == 0) {
                found = 1;
                break;
            }
        }

        rewind(fin);

        if (found) {
            printf("Phone number already exists.\n");
            fclose(fin);
            fclose(fout);
            return;
        }

        printf("Enter contact email: ");
        scanf("%49s", con.email);

        if (strchr(con.email, '@') == NULL || strchr(con.email, '.') == NULL) {

            printf("Invalid email address.\n");

            fclose(fin);
            fclose(fout);

            return;
        }

        fwrite(&con, sizeof(con), 1, fout);
        printf("Contact added successfully.\n");

    }
    fclose(fin);
    fclose(fout);
}

void viewContact() {
    FILE* fin;

    int found = 0;
    int cid;
    char cname[50];

    struct contact con;
    fin = fopen("contact.dat", "rb");
    if (fin == NULL) {
        printf("File was unable to create");
    }
    else {
        int op;
        printf("1. search by id\n2. search by name\nEnter your choice: ");
        scanf("%d", &op);

        if (op == 1) {

            printf("Enter contact id to view: ");
            scanf("%d", &cid);
            while (fread(&con, sizeof(con), 1, fin)) {
                if (cid == con.id) {
                    found = 1;
                    printf("\n=========================\n");
                    printf("Contact ID    : %d\n", con.id);
                    printf("Contact Name  : %s\n", con.name);
                    printf("Phone Number  : %s\n", con.phone);
                    printf("Email         : %s\n", con.email);
                    printf("=========================\n");

                    break;
                }
            }
        }
        else if (op == 2) {
            printf("Enter contact name to view: ");
            scanf("%49s", cname);

            while (fread(&con, sizeof(con), 1, fin)) {
                if (strcmp(cname, con.name) == 0) {
                    found = 1;
                    printf("\n=========================\n");
                    printf("Contact ID    : %d\n", con.id);
                    printf("Contact Name  : %s\n", con.name);
                    printf("Phone Number  : %s\n", con.phone);
                    printf("Email         : %s\n", con.email);
                    printf("=========================\n");

                    break;
                }
            }
        }
        else {
            printf("Invalid option");
        }
        if (!found) {
            if (op == 1){
                printf("Contact with ID %d was not found.\n", cid);
            }
            else {
                printf("Contact with name %s was not found.\n", cname);
            }
        }
        fclose(fin);
    }
}

void updateContact() {
    FILE* fout;
    FILE* fin;

    int cid, found = 0;

    struct contact con;
    fin = fopen("contact.dat", "rb");
    fout = fopen("temp.dat", "ab");

    if (fin == NULL || fout == NULL) {
        printf("error while opening or creating file");
    }
    else {
        printf("Enter Contact id to update: ");
        scanf("%d", &cid);
        while (fread(&con, sizeof(con), 1, fin)) {
            if (cid == con.id) {
                found = 1;
                printf("Contact name: ");
                scanf("%49s", con.name);
                printf("Contact number: ");
                scanf("%49s", con.phone);
                printf("Contact email: ");
                scanf("%49s", con.email);
            }
            fwrite(&con, sizeof(con), 1, fout);
        }

        fclose(fin);
        fclose(fout);
        if (!found) {
            printf("Contact with this id %d is not found: ", cid);
            remove("temp.dat");
        }
        else {
            printf("Contact updated successfully.\n");
            remove("contact.dat");
            rename("temp.dat", "contact.dat");
        }
    }

}

void deleteContact() {
    FILE* fout;
    FILE* fin;

    int cid, found = 0;

    struct contact con;
    fin = fopen("contact.dat", "rb");
    fout = fopen("temp.dat", "ab");

    if (fin == NULL || fout == NULL) {
        printf("error while opening or creating file");
    }
    else {
        printf("Enter Contact ID to delete: ");
        scanf("%d", &cid);
        while (fread(&con, sizeof(con), 1, fin)) {
            if (cid != con.id) {
                fwrite(&con, sizeof(con), 1, fout);
            }
            else {
                found = 1;
            }

        }

        fclose(fin);
        fclose(fout);
        if (!found) {
            printf("Contact with is id %d is not found: ", cid);
            remove("temp.dat");
        }
        else {
            printf("Contact deleted successfully.\n");
            remove("contact.dat");
            rename("temp.dat", "contact.dat");
        }
    }
}

void showContacts() {
    FILE* fin;

    struct contact con;
    fin = fopen("contact.dat", "rb");
    if (fin == NULL) {
        printf("File was unable to create");
    }
    else {
        if (fread(&con, sizeof(con), 1, fin) == 0) {
            printf("No contacts available.\n");
            fclose(fin);
            return;
        }

        rewind(fin);

        while (fread(&con, sizeof(con), 1, fin)) {
            printf("\n=========================\n");
            printf("Contact ID    : %d\n", con.id);
            printf("Contact Name  : %s\n", con.name);
            printf("Phone Number  : %s\n", con.phone);
            printf("Email         : %s\n", con.email);
            printf("=========================\n");
        }

        fclose(fin);
    }
}
