#include <stdio.h>
#include "Operations.h"

void add(int a, int b) {
    int c = a + b;
    printf("Sum: %d", c);
}

void sub(int a, int b) {
    int c = a - b;
    printf("difference: %d", c);
}

void multiply(int a, int b) {
    int c = a * b;
    printf("product: %d", c);
}

void divide(int a, int b) {
    if (b == 0) {
        printf("Division by zero is not possible");
    }
    else {
        int c = a / b;
        printf("quotient: %d", c);
    }
}

void modulo(int a, int b) {
    if (b != 0) {
        int c = a % b;
        printf("remainder: %d", c);
    }
    else {
        printf("Modulo by zero is not possible");
    }
}