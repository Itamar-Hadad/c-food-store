#define _CRT_SECURE_NO_WARNINGS
#ifndef __SHOPPINGITEM__
#define __SHOPPINGITEM__

#include "generalFunctions.h"

typedef struct
{
    char barcode[BARCODE_SIZE + 1]; // +1 for '\0'
    float price;
    int amount;
} ShoppingItem;

void initShoppingItem(ShoppingItem* shopping_item, const char* barcode, float price, int amount);

#endif