#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "ShoppingItem.h"
#include "list.h"

typedef struct
{
	LIST itemLList;

}ShoppingCart;


void			initCart(ShoppingCart* cart);
float			getTotalPrice(const ShoppingCart* cart);
NODE*			getInsertNode(NODE* head, const ShoppingItem* pItem, int (*compare)(const void*, const void*));
ShoppingItem*	getItemByBarocde(const LIST* itemLList, const char* barcode);
int				addItemToCart(ShoppingCart* cart, const char* barcode, float price, int count);
float			printShoppingCart(const ShoppingCart* cart);
void			freeShoppingCart(ShoppingCart* cart);