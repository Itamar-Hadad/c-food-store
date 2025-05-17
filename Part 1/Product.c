#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "Product.h"


const char* types[eNofType] = { "FV", "FR", "FZ", "SH" };
const char* pTypes[] = { "Fruit Vegtable", "Fridge","Frozen", "Shelf" };

void initProduct(Product* product) {
    initNameProduct(product);
    initProductType(product);
    initBarcode(product);
    initDate(&product->date);
    initPrice(product);
    initAmount(product);
}

void initNameProduct(Product* product) {
    printf("Enter product name up to 20 chars\n");
    myGets(product->name, PNAME_SIZE + 1);
}

void initProductType(Product* product) {
    int nType;
    do {
        nType = getType();
    } while (nType < 0 || nType > 3);
    product->type = nType;
}

int getType() {
    int nType;
    printf("\nPlease enter one of the following types\n");
    for (int i = 0; i < eNofType; i++) {
        printf("%d for %s\n", i, pTypes[i]);
    }
    scanf("%d", &nType);
    return nType;
}

const char* getTypeName(int nType) {
    const char* type = pTypes[nType];
    return type;
}

void initBarcode(Product* product) {
    int numBarcode;
    char temp[BARCODE_SIZE - 1]; //to casting the numBarcode (5 digits) to string + '/0'
    strcpy(product->barcode, types[product->type]);
    numBarcode = MIN_BARCODE + rand() % (MAX_BARCODE - MIN_BARCODE + 1);
    sprintf(temp, "%d", numBarcode);
    strcat(product->barcode, temp);
}

void initPrice(Product* product) {
    float tempPrice;
    do {
        printf("Enter product price:\n");
        scanf("%f", &tempPrice);
    } while (tempPrice < 0);
    product->price = tempPrice;
}

void initAmount(Product* product) {
    int tempAmount;
    do {
        printf("Enter product amount:\n");
        scanf("%d", &tempAmount);
    } while (tempAmount < 0);
    product->amount = tempAmount;
}

void increaseAmount(Product* product) {
    int addAmount;
    do {
        printf("How many items to add to stock?\n");
        scanf("%d", &addAmount);
    } while (addAmount <= 0);
    product->amount += addAmount;
}

int decreaseAmount(Product* product) {
    int amount;
    if (product->amount == 0) {
        printf("This product out of stock\n");
        return -1;
    }
    do {
        printf("How many items do you want? max %d\n", product->amount);
        scanf("%d", &amount);
    } while (amount <= 0 || amount > product->amount);
    product->amount -= amount;
    return amount;
}

int verifyBarcodeStructure(const char* barcode) {
    if (strlen(barcode) != BARCODE_SIZE) {
        printf("Invalid barcode length\n");
        return 0;
    }
    if (!(barcode[0] == 'S' && barcode[1] == 'H') &&
        !(barcode[0] == 'F' && barcode[1] == 'Z') &&
        !(barcode[0] == 'F' && barcode[1] == 'R') &&
        !(barcode[0] == 'F' && barcode[1] == 'V')
        ) {
        printf("Invalid type prefix\n");
        return 0;
    }
    for (int i = 2; i < BARCODE_SIZE; i++) {
        if (!isdigit(barcode[i])) {
            printf("Only digits after type prefix\n");
            printf("Inccorect number of digits\n");
            return 0;
        }
    }
    return 1;
}

void showProduct(const Product* product) {
    printf("%-20s%-10s%-20s%-10.2f%-20d",
        product->name, product->barcode, pTypes[product->type], product->price, product->amount);
    showDate(&product->date);
}

void printProductBarcodeRules() {
    printf("Code should be of 7 length exactly\n");
    printf("Must have 2 type prefix letters followed by a 5 digits number\n");
    printf("For example: FR20301\n");
}

