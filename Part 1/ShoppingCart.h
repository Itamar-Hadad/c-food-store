#define _CRT_SECURE_NO_WARNINGS
#ifndef __SHOPPINGCART__
#define __SHOPPINGCART__

#include "ShoppingItem.h"

typedef struct
{
    int amount;
    ShoppingItem** Items;
} ShoppingCart;
void initShoppingCart(ShoppingCart* shoppingCart);
int addItem(ShoppingCart* shoppingCart, const char* barcode, float price, int amount);
float calculatePrice(const ShoppingCart* shoppingCart);
void showCart(const ShoppingCart* shoppingCart);
void freeCart(ShoppingCart* shoppingCart);
#endif