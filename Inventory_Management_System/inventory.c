#include "inventory.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void displayProduct(struct Product product) {
    printf("\n====================================================");
    printf("\n                 PRODUCT DETAILS");
    printf("\n====================================================");

    printf("\nProduct ID      : %d", product.productId);
    printf("\nProduct Name    : %s", product.productName);
    printf("\nCategory        : %s", product.category);
    printf("\nSupplier        : %s", product.supplier);
    printf("\nPrice           : ₹%.2f", product.price);
    printf("\nQuantity        : %d", product.quantity);
    printf("\nReorder Level   : %d", product.reorderLevel);

    printf("\n----------------------------------------------------");

    if (product.quantity == 0) {
        printf("\nStock Status    : Out of Stock");
    } else if (product.quantity <= product.reorderLevel) {
        printf("\nStock Status    : Low Stock");
    } else {
        printf("\nStock Status    : In Stock");
    }

    printf("\n====================================================\n");
}

void addProduct() {
    struct Product product;
    struct Product temp;
    FILE *fp;
    int found = 0;
    int categoryChoice;

    printf("\n========== ADD PRODUCT ==========\n");


    printf("Enter Product ID: ");
    if (scanf_s("%d", &product.productId) != 1 ||
        product.productId <= 0) {
        printf("Invalid Product ID!\n");
        while (getchar() != '\n');
        return;
    }


    fp = fopen("products.dat", "rb");

    if (fp != NULL) {
        while (fread(&temp, sizeof(struct Product), 1, fp) == 1) {
            if (temp.productId == product.productId) {
                found = 1;
                break;
            }
        }
        fclose(fp);
    }

    if (found) {
        printf("Product ID already exists!\n");
        return;
    }

    printf("Enter Product Name: ");
    scanf_s(" %49[^\n]", product.productName);

    printf("\nSelect Category:\n");
    printf("1. Electronics\n");
    printf("2. Grocery\n");
    printf("3. Stationery\n");
    printf("4. Clothing\n");
    printf("5. Furniture\n");
    printf("Enter your choice: ");

    if (scanf_s("%d", &categoryChoice) != 1) {
        printf("Invalid category choice!\n");
        while (getchar() != '\n');
        return;
    }

    switch (categoryChoice) {
        case 1:
            strcpy(product.category, "Electronics");
            break;
        case 2:
            strcpy(product.category, "Grocery");
            break;
        case 3:
            strcpy(product.category, "Stationery");
            break;
        case 4:
            strcpy(product.category, "Clothing");
            break;
        case 5:
            strcpy(product.category, "Furniture");
            break;
        default:
            printf("Invalid category!\n");
            return;
    }

    printf("Enter Supplier Name: ");
    scanf_s(" %49[^\n]", product.supplier);

    printf("Enter Price: ");
    if (scanf_s("%f", &product.price) != 1 ||
        product.price <= 0) {
        printf("Invalid price!\n");
        while (getchar() != '\n');
        return;
    }

    printf("Enter Quantity: ");
    if (scanf_s("%d", &product.quantity) != 1 ||
        product.quantity < 0) {
        printf("Invalid quantity!\n");
        while (getchar() != '\n');
        return;
    }

    printf("Enter Reorder Level: ");
    if (scanf_s("%d", &product.reorderLevel) != 1 ||
        product.reorderLevel < 0) {
        printf("Invalid reorder level!\n");
        while (getchar() != '\n');
        return;
    }

    fp = fopen("products.dat", "ab");

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    if (fwrite(&product, sizeof(struct Product), 1, fp) == 1) {
        printf("\nProduct added successfully!\n");
    } else {
        printf("\nError saving product!\n");
    }

    fclose(fp);
}

void viewProduct() {
    struct Product product;

    FILE *fout;
    int found = 0, id;

    printf("Enter Product ID: ");
    if (scanf("%d", &id) != 1 || id <= 0) {
        printf("Invalid Product ID!\n");
        while (getchar() != '\n');
        return;
    }

    fout = fopen("products.dat", "rb");

    if (fout == NULL) {
        printf("Error opening file!\n");
        while (getchar() != '\n');
        return;
    }

    while (fread(&product, sizeof(struct Product), 1, fout) == 1) {
        if (product.productId == id) {
            displayProduct(product);
            found = 1;
            break;
        }
    }

    fclose(fout);

    if (!found) {
        printf("Product not found!\n");
    }
}


void searchProduct() {
    struct Product product;
    FILE *fin;
    int found = 0, id, choice;
    char name[50], category[30];

    printf("\n1. Search Product by ID\n");
    printf("2. Search Product by Name\n");
    printf("3. Search Product by Category\n");
    printf("Enter your choice: ");

    if (scanf("%d", &choice) != 1 || choice < 1 || choice > 3) {
        printf("Invalid choice!\n");
        while (getchar() != '\n');
        return;
    }

    switch (choice) {
        case 1:
            printf("Enter Product ID: ");
            if (scanf("%d", &id) != 1 || id <= 0) {
                printf("Invalid product ID!\n");
                while (getchar() != '\n');
                return;
            }
            break;

        case 2:
            printf("Enter Product Name: ");
            if (scanf(" %49[^\n]", name) != 1) {
                printf("Invalid product name!\n");
                return;
            }
            break;

        case 3:
            printf("Enter Product Category: ");
            if (scanf(" %29[^\n]", category) != 1) {
                printf("Invalid product category!\n");
                return;
            }
            break;
    }

    fin = fopen("products.dat", "rb");

    if (fin == NULL) {
        printf("Error opening file!\n");
        return;
    }

    while (fread(&product, sizeof(struct Product), 1, fin) == 1) {
        if (choice == 1 && product.productId == id) {
            displayProduct(product);
            found = 1;
            break;
        } else if (choice == 2 &&
                   strcmp(name, product.productName) == 0) {
            displayProduct(product);
            found = 1;
        } else if (choice == 3 &&
                   strcmp(category, product.category) == 0) {
            displayProduct(product);
            found = 1;
        }
    }

    if (ferror(fin)) {
        printf("Error reading product records!\n");
    }

    fclose(fin);

    if (!found) {
        printf("Product not found!\n");
    }
}


void updateProduct() {
    struct Product product;
    FILE *fin, *fout;
    int id, found = 0, choice;

    printf("\n========== UPDATE PRODUCT ==========\n");
    printf("Enter Product ID: ");

    if (scanf("%d", &id) != 1 || id <= 0) {
        printf("Invalid Product ID!\n");
        while (getchar() != '\n');
        return;
    }

    fin = fopen("products.dat", "rb");

    if (fin == NULL) {
        printf("Error opening product file!\n");
        return;
    }

    fout = fopen("temp.dat", "wb");

    if (fout == NULL) {
        printf("Error creating temporary file!\n");
        fclose(fin);
        return;
    }

    while (fread(&product, sizeof(struct Product), 1, fin) == 1) {
        if (product.productId == id) {
            found = 1;

            printf("\nCurrent Product Details:\n");
            displayProduct(product);

            printf("\nSelect field to update:\n");
            printf("1. Product Name\n");
            printf("2. Category\n");
            printf("3. Supplier\n");
            printf("4. Price\n");
            printf("5. Quantity\n");
            printf("6. Reorder Level\n");
            printf("7. Update All\n");
            printf("Enter your choice: ");

            if (scanf("%d", &choice) != 1 ||
                choice < 1 || choice > 7) {
                printf("Invalid choice!\n");
                fclose(fin);
                fclose(fout);
                remove("temp.dat");
                return;
            }

            if (choice == 1 || choice == 7) {
                printf("Enter New Product Name: ");
                if (scanf(" %49[^\n]", product.productName) != 1) {
                    printf("Invalid name!\n");
                    fclose(fin);
                    fclose(fout);
                    remove("temp.dat");
                    return;
                }
            }

            if (choice == 2 || choice == 7) {
                printf("Enter New Category:\n");
                printf("1. Electronics\n");
                printf("2. Grocery\n");
                printf("3. Stationery\n");
                printf("4. Clothing\n");
                printf("5. Furniture\n");
                printf("Enter choice: ");

                int categoryChoice;
                if (scanf("%d", &categoryChoice) != 1) {
                    printf("Invalid category!\n");
                    fclose(fin);
                    fclose(fout);
                    remove("temp.dat");
                    return;
                }

                switch (categoryChoice) {
                    case 1:
                        strcpy(product.category, "Electronics");
                        break;
                    case 2:
                        strcpy(product.category, "Grocery");
                        break;
                    case 3:
                        strcpy(product.category, "Stationery");
                        break;
                    case 4:
                        strcpy(product.category, "Clothing");
                        break;
                    case 5:
                        strcpy(product.category, "Furniture");
                        break;
                    default:
                        printf("Invalid category!\n");
                        fclose(fin);
                        fclose(fout);
                        remove("temp.dat");
                        return;
                }
            }

            if (choice == 3 || choice == 7) {
                printf("Enter New Supplier Name: ");
                if (scanf(" %49[^\n]", product.supplier) != 1) {
                    printf("Invalid supplier!\n");
                    fclose(fin);
                    fclose(fout);
                    remove("temp.dat");
                    return;
                }
            }

            if (choice == 4 || choice == 7) {
                printf("Enter New Price: ");
                if (scanf("%f", &product.price) != 1 ||
                    product.price <= 0) {
                    printf("Invalid price!\n");
                    fclose(fin);
                    fclose(fout);
                    remove("temp.dat");
                    return;
                }
            }

            if (choice == 5 || choice == 7) {
                printf("Enter New Quantity: ");
                if (scanf("%d", &product.quantity) != 1 ||
                    product.quantity < 0) {
                    printf("Invalid quantity!\n");
                    fclose(fin);
                    fclose(fout);
                    remove("temp.dat");
                    return;
                }
            }

            if (choice == 6 || choice == 7) {
                printf("Enter New Reorder Level: ");
                if (scanf("%d", &product.reorderLevel) != 1 ||
                    product.reorderLevel < 0) {
                    printf("Invalid reorder level!\n");
                    fclose(fin);
                    fclose(fout);
                    remove("temp.dat");
                    return;
                }
            }
        }

        if (fwrite(&product, sizeof(struct Product), 1, fout) != 1) {
            printf("Error writing product record!\n");
            fclose(fin);
            fclose(fout);
            remove("temp.dat");
            return;
        }
    }

    if (ferror(fin)) {
        printf("Error reading product records!\n");
        fclose(fin);
        fclose(fout);
        remove("temp.dat");
        return;
    }

    fclose(fin);

    if (fclose(fout) != 0) {
        printf("Error closing temporary file!\n");
        remove("temp.dat");
        return;
    }

    if (!found) {
        printf("Product not found!\n");
        remove("temp.dat");
        return;
    }

    if (remove("products.dat") != 0) {
        printf("Error replacing original file!\n");
        remove("temp.dat");
        return;
    }

    if (rename("temp.dat", "products.dat") != 0) {
        printf("Error renaming temporary file!\n");
        printf("Your original file may need recovery.\n");
        return;
    }

    printf("\nProduct updated successfully!\n");
}


void deleteProduct() {
    struct Product product;
    FILE *fin, *fout;
    int id, found = 0;

    printf("\n========== DELETE PRODUCT ==========\n");
    printf("Enter Product ID: ");

    if (scanf("%d", &id) != 1 || id <= 0) {
        printf("Invalid Product ID!\n");
        while (getchar() != '\n');
        return;
    }

    fin = fopen("products.dat", "rb");

    if (fin == NULL) {
        printf("Error opening product file!\n");
        return;
    }

    fout = fopen("temp.dat", "wb");

    if (fout == NULL) {
        printf("Error creating temporary file!\n");
        fclose(fin);
        return;
    }

    while (fread(&product, sizeof(struct Product), 1, fin) == 1) {
        if (product.productId == id) {
            found = 1;
            printf("\nProduct found:\n");
            displayProduct(product);
            continue;
        }

        if (fwrite(&product, sizeof(struct Product), 1, fout) != 1) {
            printf("Error writing product records!\n");
            fclose(fin);
            fclose(fout);
            remove("temp.dat");
            return;
        }
    }

    if (ferror(fin)) {
        printf("Error reading product records!\n");
        fclose(fin);
        fclose(fout);
        remove("temp.dat");
        return;
    }

    fclose(fin);

    if (fclose(fout) != 0) {
        printf("Error closing temporary file!\n");
        remove("temp.dat");
        return;
    }

    if (!found) {
        printf("Product not found!\n");
        remove("temp.dat");
        return;
    }

    if (remove("products.dat") != 0) {
        printf("Error deleting original file!\n");
        remove("temp.dat");
        return;
    }

    if (rename("temp.dat", "products.dat") != 0) {
        printf("Error renaming temporary file!\n");
        printf("Original file may need recovery.\n");
        return;
    }

    printf("\nProduct deleted successfully!\n");
}


void purchaseStock() {
    struct Product product;
    FILE *fin, *fout;
    int id, quantity, found = 0;

    printf("\n========== PURCHASE STOCK ==========\n");

    printf("Enter Product ID: ");
    if (scanf("%d", &id) != 1 || id <= 0) {
        printf("Invalid Product ID!\n");
        while (getchar() != '\n');
        return;
    }

    printf("Enter Quantity to Purchase: ");
    if (scanf("%d", &quantity) != 1 || quantity <= 0) {
        printf("Invalid quantity!\n");
        while (getchar() != '\n');
        return;
    }

    fin = fopen("products.dat", "rb");

    if (fin == NULL) {
        printf("Error opening product file!\n");
        return;
    }

    fout = fopen("temp.dat", "wb");

    if (fout == NULL) {
        printf("Error creating temporary file!\n");
        fclose(fin);
        return;
    }

    while (fread(&product, sizeof(struct Product), 1, fin) == 1) {
        if (product.productId == id) {
            found = 1;

            if (quantity > 2147483647 - product.quantity) {
                printf("Quantity is too large!\n");
                fclose(fin);
                fclose(fout);
                remove("temp.dat");
                return;
            }

            product.quantity += quantity;

            printf("\nStock purchased successfully!\n");
            printf("Product Name: %s\n", product.productName);
            printf("Purchased Quantity: %d\n", quantity);
            printf("Updated Stock: %d\n", product.quantity);
        }

        if (fwrite(&product, sizeof(struct Product), 1, fout) != 1) {
            printf("Error writing product records!\n");
            fclose(fin);
            fclose(fout);
            remove("temp.dat");
            return;
        }
    }

    if (ferror(fin)) {
        printf("Error reading product records!\n");
        fclose(fin);
        fclose(fout);
        remove("temp.dat");
        return;
    }

    fclose(fin);

    if (fclose(fout) != 0) {
        printf("Error closing temporary file!\n");
        remove("temp.dat");
        return;
    }

    if (!found) {
        printf("Product not found!\n");
        remove("temp.dat");
        return;
    }

    if (remove("products.dat") != 0) {
        printf("Error replacing product file!\n");
        remove("temp.dat");
        return;
    }

    if (rename("temp.dat", "products.dat") != 0) {
        printf("Error renaming temporary file!\n");
        printf("Original file may need recovery.\n");
        return;
    }

    printf("\nStock updated successfully!\n");
}


void sellProduct() {
    struct Product product;
    FILE *fin, *fout;
    int id, quantity, found = 0;

    printf("\n========== SELL PRODUCT ==========\n");

    printf("Enter Product ID: ");
    if (scanf("%d", &id) != 1 || id <= 0) {
        printf("Invalid Product ID!\n");
        while (getchar() != '\n');
        return;
    }

    printf("Enter Quantity to Sell: ");
    if (scanf("%d", &quantity) != 1 || quantity <= 0) {
        printf("Invalid quantity!\n");
        while (getchar() != '\n');
        return;
    }

    fin = fopen("products.dat", "rb");

    if (fin == NULL) {
        printf("Error opening product file!\n");
        return;
    }

    fout = fopen("temp.dat", "wb");

    if (fout == NULL) {
        printf("Error creating temporary file!\n");
        fclose(fin);
        return;
    }

    while (fread(&product, sizeof(struct Product), 1, fin) == 1) {
        if (product.productId == id) {
            found = 1;

            if (product.quantity < quantity) {
                printf("Insufficient stock!\n");
                printf("Available Stock: %d\n", product.quantity);
                fclose(fin);
                fclose(fout);
                remove("temp.dat");
                return;
            }

            product.quantity -= quantity;

            printf("\nProduct sold successfully!\n");
            printf("Product Name: %s\n", product.productName);
            printf("Quantity Sold: %d\n", quantity);
            printf("Remaining Stock: %d\n", product.quantity);
        }

        if (fwrite(&product, sizeof(struct Product), 1, fout) != 1) {
            printf("Error writing product records!\n");
            fclose(fin);
            fclose(fout);
            remove("temp.dat");
            return;
        }
    }

    if (ferror(fin)) {
        printf("Error reading product records!\n");
        fclose(fin);
        fclose(fout);
        remove("temp.dat");
        return;
    }

    fclose(fin);

    if (fclose(fout) != 0) {
        printf("Error closing temporary file!\n");
        remove("temp.dat");
        return;
    }

    if (!found) {
        printf("Product not found!\n");
        remove("temp.dat");
        return;
    }

    if (remove("products.dat") != 0) {
        printf("Error replacing product file!\n");
        remove("temp.dat");
        return;
    }

    if (rename("temp.dat", "products.dat") != 0) {
        printf("Error renaming temporary file!\n");
        printf("Original file may need recovery.\n");
        return;
    }

    printf("\nStock updated successfully!\n");
}


void checkLowStock() {
    struct Product product;
    FILE *fin;
    int found = 0;

    printf("\n========== LOW STOCK PRODUCTS ==========\n");

    fin = fopen("products.dat", "rb");

    if (fin == NULL) {
        printf("Error opening product file!\n");
        return;
    }

    while (fread(&product, sizeof(struct Product), 1, fin) == 1) {
        if (product.quantity <= product.reorderLevel) {
            displayProduct(product);
            found = 1;
        }
    }

    if (ferror(fin)) {
        printf("Error reading product records!\n");
        fclose(fin);
        return;
    }

    fclose(fin);

    if (!found) {
        printf("No low stock products found!\n");
    }
}


void stockReport() {
    struct Product product;
    FILE *fin;
    int count = 0;
    float totalValue = 0;

    printf("\n================ STOCK REPORT ================\n");

    fin = fopen("products.dat", "rb");

    if (fin == NULL) {
        printf("Error opening product file!\n");
        return;
    }

    printf("\n%-8s %-20s %-12s %-10s %-12s %-15s\n",
           "ID", "Name", "Price", "Quantity", "Stock Value", "Status");

    printf("--------------------------------------------------------------------------\n");

    while (fread(&product, sizeof(struct Product), 1, fin) == 1) {
        float stockValue = product.price * product.quantity;

        printf("%-8d %-20s ₹%-11.2f %-10d ₹%-11.2f ",
               product.productId,
               product.productName,
               product.price,
               product.quantity,
               stockValue);

        if (product.quantity == 0) {
            printf("%-15s\n", "Out of Stock");
        } else if (product.quantity <= product.reorderLevel) {
            printf("%-15s\n", "Low Stock");
        } else {
            printf("%-15s\n", "In Stock");
        }

        totalValue += stockValue;
        count++;
    }

    if (ferror(fin)) {
        printf("\nError reading product records!\n");
        fclose(fin);
        return;
    }

    fclose(fin);

    printf("--------------------------------------------------------------------------\n");
    printf("Total Products       : %d\n", count);
    printf("Total Inventory Value: ₹%.2f\n", totalValue);
    printf("================================================\n");
}


void totalInventoryValue() {
    struct Product product;
    FILE *fin;
    float totalValue = 0;
    int count = 0;

    printf("\n====== TOTAL INVENTORY VALUE ======\n");

    fin = fopen("products.dat", "rb");

    if (fin == NULL) {
        printf("Error opening product file!\n");
        return;
    }

    while (fread(&product, sizeof(struct Product), 1, fin) == 1) {
        totalValue += product.price * product.quantity;
        count++;
    }

    if (ferror(fin)) {
        printf("Error reading product records!\n");
        fclose(fin);
        return;
    }

    fclose(fin);

    if (count == 0) {
        printf("No products found!\n");
        return;
    }

    printf("\nTotal Products        : %d\n", count);
    printf("Total Inventory Value : ₹%.2f\n", totalValue);
    printf("====================================\n");
}


void outOfStockProducts() {
    struct Product product;
    FILE *fin;
    int found = 0;

    printf("\n========== OUT OF STOCK PRODUCTS ==========\n");

    fin = fopen("products.dat", "rb");

    if (fin == NULL) {
        printf("Error opening product file!\n");
        return;
    }

    while (fread(&product, sizeof(struct Product), 1, fin) == 1) {
        if (product.quantity == 0) {
            displayProduct(product);
            found = 1;
        }
    }

    if (ferror(fin)) {
        printf("Error reading product records!\n");
        fclose(fin);
        return;
    }

    fclose(fin);

    if (!found) {
        printf("No out-of-stock products found!\n");
    }
}


void showAllProducts() {
    struct Product product;
    FILE *fin;
    int count = 0;

    printf("\n========== ALL PRODUCTS ==========\n");

    fin = fopen("products.dat", "rb");

    if (fin == NULL) {
        printf("Error opening product file!\n");
        return;
    }

    while (fread(&product, sizeof(struct Product), 1, fin) == 1) {
        displayProduct(product);
        count++;
    }

    if (ferror(fin)) {
        printf("Error reading product records!\n");
        fclose(fin);
        return;
    }

    fclose(fin);

    if (count == 0) {
        printf("No products found!\n");
    } else {
        printf("\nTotal Products: %d\n", count);
    }
}
