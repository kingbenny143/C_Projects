#include <stdio.h>
#include<stdlib.h>
#include<time.h>

int main(void) {
    int secretNumber;
    int guess;
    int attempts = 0;
    int level;

    printf("\n==========Welcome to the number guessing game=========");
    printf("\n1. Easy (1-10)\n2. Medium (1-50)\n3. Hard (1-100)\n4.Exit\nEnter the level of difficulty: ");
    scanf("%d",&level);

    if (level == 1) {
        srand(time(NULL));
        secretNumber = rand() % 10;
    }
    else if (level == 2) {
        srand(time(NULL));
        secretNumber = rand() % 50;
    }
    else if (level == 3) {
        srand(time(NULL));
        secretNumber = rand() % 100;
    }

   while (1) {
       printf("Enter your guess (1-100): ");
       scanf("%d", &guess);

       attempts++;

       if (guess > secretNumber) {
           printf("Too High! \n");
       }
       else if (guess < secretNumber) {
           printf("Too Low!\n");
       }
       else {
           printf("Correct!\n");
           printf("Attempts: %d\n", attempts);
           break;
       }

   }
    return 0;   
}
