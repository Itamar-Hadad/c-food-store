#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include  "ShoppingItem.h"


void	printItem(const ShoppingItem* pItem)
{
	printf("Item %s count %d price per item %.2f\n", pItem->barcode, pItem->count, pItem->price);
}

ShoppingItem*	createItem(const char* barcode, float price, int count)
{
	ShoppingItem* pItem = (ShoppingItem*)malloc(1 * sizeof(ShoppingItem));
	if (!pItem)
		return NULL;
	strcpy(pItem->barcode, barcode);
	pItem->price = price;
	pItem->count = count;
	return pItem;
}

int compareItemBarcode(const void* v1, const void* v2) {
	const ShoppingItem* item1 = (const ShoppingItem*)v1;
	const ShoppingItem* item2 = (const ShoppingItem*)v2;
	return strcmp(item1->barcode, item2->barcode);
}