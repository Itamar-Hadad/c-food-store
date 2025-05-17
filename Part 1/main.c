#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "SuperMarket.h"

void printMenu() {
    printf("\nPlease choose one of the following options\n");
    printf("0 - Show SuperMarket\n");
    printf("1 - Add Product\n");
    printf("2 - Add Customer\n");
    printf("3 - Customer Shopping\n");
    printf("4 - Print Shopping Cart\n");
    printf("5 - Customer Shopping Cart Management\n");
    printf("6 - Print Product By Type\n");
    printf("-1 - Quit\n");
    printf("Enter your choice: ");
}

int main() {
    srand((unsigned)time(NULL));
    SuperMarket superMarket;

    if (!initMarket(&superMarket)) {
        printf("Failed to initialize the supermarket. Exiting...\n");
        return EXIT_FAILURE;
    }

    int choice;
    do {
        printMenu();
        scanf("%d", &choice);

        switch (choice) {
        case 0:
            showSuperMarket(&superMarket);
            break;
        case 1:
            if (!addProduct(&superMarket))
                printf("Failed to add product.\n");

            break;
        case 2:
            if (!addCustomer(&superMarket))
                printf("Failed to add customer.\n");
            break;
        case 3:
            if (shoppingProcess(&superMarket) != 2)
                printf("Shopping process ended with an error.\n");
            break;
        case 4:
            showCustomerCart(&superMarket);
            break;
        case 5:
            shoppingCartManagement(&superMarket);
            break;
        case 6:
            showProductByType(&superMarket);
            break;
        case -1:

            exitProgram(&superMarket);
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    } while (choice != -1);

    return EXIT_SUCCESS;
}
