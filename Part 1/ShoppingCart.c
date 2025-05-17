#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ShoppingCart.h"

void initShoppingCart(ShoppingCart* shoppingCart) {
    shoppingCart->amount = 0;
    shoppingCart->Items = NULL;
}

int addItem(ShoppingCart* shoppingCart, const char* barcode, float price, int amount) {
    ShoppingItem** temp;
    //Check if the item is already exist so we just need to increase the amount
    for (int i = 0; i < shoppingCart->amount; i++) {
        if (strcmp(shoppingCart->Items[i]->barcode, barcode) == 0) {
            shoppingCart->Items[i]->amount += amount;
            return 1;
        }
    }
    ShoppingItem* newItem = (ShoppingItem*)malloc(sizeof(ShoppingItem));
    if (!newItem)
        return 0;
    initShoppingItem(newItem, barcode, price, amount);
    temp = (ShoppingItem**)realloc(shoppingCart->Items,
        (amount + 1) * sizeof(ShoppingItem*));
    if (!temp) {
        free(newItem);
        freeCart(shoppingCart);
        return 0;
    }
    shoppingCart->Items = temp;
    shoppingCart->Items[shoppingCart->amount] = newItem;
    shoppingCart->amount++;
    return 1;
}

float calculatePrice(const ShoppingCart* shoppingCart) {
    float totalPrice = 0;
    for (int i = 0; i < shoppingCart->amount; i++) {
        totalPrice += shoppingCart->Items[i]->amount * shoppingCart->Items[i]->price;
    }
    return totalPrice;
}

void showCart(const ShoppingCart* shoppingCart) {
    char* barcode;
    int amount;
    float price;

    if (shoppingCart == NULL) {
        printf("Empty ShoppingCart\n");
        return;
    }

    for (int i = 0; i < shoppingCart->amount; i++) {
        barcode = shoppingCart->Items[i]->barcode;
        amount = shoppingCart->Items[i]->amount;
        price = shoppingCart->Items[i]->price;
        printf("Item %s count %d price per item %.2f\n", barcode, amount, price);
    }
    float totalPrice = calculatePrice(shoppingCart);
    printf("Total bill to pay: %.2f\n", totalPrice);
}

void freeCart(ShoppingCart* shoppingCart) {
    for (int i = 0; i < shoppingCart->amount; i++) {
        free(shoppingCart->Items[i]);
    }
    free(shoppingCart->Items);
}

