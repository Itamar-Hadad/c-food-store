#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "Product.h"

typedef struct
{
	char		barcode[BARCODE_LENGTH + 1];
	float		price;
	int			count;
}ShoppingItem;

void			printItem(const ShoppingItem* pItem);
ShoppingItem*	createItem(const char* barcode, float price, int count);
int compareItemBarcode(const void* v1, const void* v2);