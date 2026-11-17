#ifndef INVENTORY_MANAGEMENT_SYSTEM_INVENTORY_H
#define INVENTORY_MANAGEMENT_SYSTEM_INVENTORY_H

struct Product {
    int productId;
    char productName[50];
    char category[30];
    char supplier[50];
    float price;
    int quantity;
    int reorderLevel;
};

void displayProduct(struct Product product);

void addProduct(void);

void viewProduct(void);

void searchProduct(void);

void updateProduct(void);

void deleteProduct(void);

void purchaseStock(void);

void sellProduct(void);

void checkLowStock(void);

void stockReport(void);

void totalInventoryValue(void);

void outOfStockProducts(void);

void showAllProducts(void);

#endif
