#include <stdio.h>
#include <stdlib.h>
#include "inventory.h"

int main(void) {

    int choice;

    while (1) {

        printf("\n=========================================================\n");
        printf("              INVENTORY MANAGEMENT SYSTEM\n");
        printf("=========================================================\n");

        printf("\nProduct Management");
        printf("\n-------------------------");
        printf("\n1. Add Product");
        printf("\n2. View Product");
        printf("\n3. Search Product");
        printf("\n4. Update Product");
        printf("\n5. Delete Product");
        printf("\n6. Show All Products");

        printf("\n\nInventory Operations");
        printf("\n-------------------------");
        printf("\n7. Purchase Stock");
        printf("\n8. Sell Product");
        printf("\n9. Check Low Stock");
        printf("\n10. Stock Report");

        printf("\n\nReports");
        printf("\n-------------------------");
        printf("\n11. Total Inventory Value");
        printf("\n12. Out of Stock Products");

        printf("\n\nSystem");
        printf("\n-------------------------");
        printf("\n13. Exit");

        printf("\n=========================================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                addProduct();
                break;

            case 2:
                viewProduct();
                break;

            case 3:
                searchProduct();
                break;

            case 4:
                updateProduct();
                break;

            case 5:
                deleteProduct();
                break;

            case 6:
                showAllProducts();
                break;

            case 7:
                purchaseStock();
                break;

            case 8:
                sellProduct();
                break;

            case 9:
                checkLowStock();
                break;

            case 10:
                stockReport();
                break;

            case 11:
                totalInventoryValue();
                break;

            case 12:
                outOfStockProducts();
                break;

            case 13:
                printf("\nThank you for using Inventory Management System.\n");
                exit(0);

            default:
                printf("\nInvalid Choice! Please enter a number between 1 and 13.\n");
        }
    }

    return 0;
}
