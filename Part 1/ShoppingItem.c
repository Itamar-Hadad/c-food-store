#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include "ShoppingItem.h"



void initShoppingItem(ShoppingItem* shopping_item, const char* barcode, float price, int amount) {
    strcpy(shopping_item->barcode, barcode);
    shopping_item->price = price;
    shopping_item->amount = amount;
}
