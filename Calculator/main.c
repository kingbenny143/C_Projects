#include <stdio.h>
#include "Operations.h"

int main() {
    int op;
    int num1, num2;
    while (1) {
        printf("\n");
        printf("\nWelcome to the Calculator by Anish Raj");
        printf("\n");

        printf("1.Add Numbers");
        printf("\n2.substract Numbers");
        printf("\n3.multiply Numbers");
        printf("\n4.divide Numbers");
        printf("\n5.modular Numbers");
        printf("\n6.exit");
        printf("\nChoose the operation type: ");
        scanf("%d", &op);


        if ( op == 1 ) {
            printf("Enter The First Number: ");
            scanf("%d", &num1);
            printf("Enter The Second Number: ");
            scanf("%d", &num2);
            add(num1, num2);
        }
        else if ( op == 2 ) {
            printf("Enter The First Number: ");
            scanf("%d", &num1);
            printf("Enter The Second Number: ");
            scanf("%d", &num2);
            sub(num1, num2);
        }
        else if ( op == 3 ) {
            printf("Enter The First Number: ");
            scanf("%d", &num1);
            printf("Enter The Second Number: ");
            scanf("%d", &num2);
            multiply(num1, num2);
        }
        else if ( op == 4 ) {
            printf("Enter The First Number: ");
            scanf("%d", &num1);
            printf("Enter The Second Number: ");
            scanf("%d", &num2);
            divide(num1, num2);
        }
        else if ( op == 5 ) {
            printf("Enter The First Number: ");
            scanf("%d", &num1);
            printf("Enter The Second Number: ");
            scanf("%d", &num2);
            modulo(num1, num2);
        }
        else if ( op == 6 ) {
            printf("Thank you....");
            break;
        }
    }

    return 0;
}
