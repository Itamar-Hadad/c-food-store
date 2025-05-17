#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ShoppingCart.h"

void	initCart(ShoppingCart* cart)
{
	L_init(&cart->itemLList);
}

float	getTotalPrice(const ShoppingCart* cart)
{
	float price = 0;
	ShoppingItem* pItem;
	NODE* pNode = cart->itemLList.head.next;
	while(pNode != NULL) {
		pItem = pNode->key;
		price += pItem->price * pItem->count;
		pNode = pNode->next;
	}
	return price;
}
NODE* getInsertNode(NODE* head, const ShoppingItem* pItem, int (*compare)(const void*, const void*)) {
	NODE* pNode = head;
	while(pNode->next != NULL) {
		if(compare(pNode->next->key, pItem) > 0)
			return pNode;
		pNode = pNode->next;
	}
	return pNode;
}

int		addItemToCart(ShoppingCart* cart, const char* barcode, float price, int count)
{
	ShoppingItem* pItem = getItemByBarocde(&cart->itemLList, barcode);
	if (!pItem) //new item
	{
		pItem = createItem(barcode, price, count);
		if (!pItem)
			return 0;

		NODE* pNodeToInsert = getInsertNode(&cart->itemLList.head, pItem, compareItemBarcode);

		if (L_insert(pNodeToInsert, pItem) == NULL)
			return 0;
	}
	else {
		pItem->count += count;
	}
	return 1;
}

float	printShoppingCart(const ShoppingCart* cart)
{
	float price;
	price = getTotalPrice(cart);
	L_print(&cart->itemLList, printItem);
	return price;
}



ShoppingItem*	getItemByBarocde(const LIST* itemLList, const char* barcode)
{
	ShoppingItem item;
	strcpy(item.barcode, barcode);
	const NODE* pNode = L_find(itemLList->head.next, &item, compareItemBarcode);
	if(pNode == NULL)
		return NULL;
	return (ShoppingItem*)pNode->key;
}

void	freeShoppingCart(ShoppingCart* cart)
{
	L_free(&cart->itemLList, free);
}

