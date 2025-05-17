#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Supermarket.h"
#include "Product.h"
#include "Customer.h"
#include "General.h"
#include "member.h"
#include "ShoppingCart.h"

static char* sortTypes[eNofProductType] = {"Not Sorted", "Name", "Count", "Price"};

void basicInitSuperMarket(SuperMarket* pMarket) {
	pMarket->customerCount = 0;
	pMarket->customerArr = NULL;
	pMarket->productCount = 0;
	pMarket->productArr = NULL;
	pMarket->sortType = 0;
}

int readFiles(SuperMarket* pMarket) {

	if(!readSuperMarket("SuperMarket.bin", pMarket)) {
		printf("Error read Supermarket\n");
		return 0;
	}

	if(!readCustomers("Customers.txt", pMarket)) {
		printf("Error read Customers\n");
		free(pMarket->name);
		freeProducts(pMarket);
		return 0;
	}
	return 1;
}

int		initSuperMarket(SuperMarket* pMarket)
{
	basicInitSuperMarket(pMarket);
	if(readFiles(pMarket)) {
		printf("Supermarket successfully loaded from files\n");
		return 1;
	}
	basicInitSuperMarket(pMarket);
	pMarket->name = getStrExactLength("Enter market name");
	if (!pMarket->name)
		return 0;
	return 1;
}

void	printSuperMarket(const SuperMarket* pMarket)
{
	printf("Super Market Name: %s\t", pMarket->name);
	printf("\n");
	printAllProducts(pMarket);
	printf("\n");
	printAllCustomers(pMarket);
}

int		addProduct(SuperMarket* pMarket)
{
	char answer;
	char barcode[BARCODE_LENGTH + 1];
	Product* pProd = NULL;

	printf("\n");
	printf("Adding new product? y/Y: ");
	scanf("%c", &answer);
	getchar();

	if (toupper(answer) == 'Y')
	{
		if (!addNewProduct(pMarket))
		{
			free(pProd);
			return 0;
		}
		return 1;
	}
	else if (pMarket->productCount > 0)
	{
		printf("Do you want to increase the amount of an existing product? y/Y: ");
		scanf("%c", &answer);
		getchar();
		if (toupper(answer) == 'Y')
		{
			printAllProducts(pMarket);
			pProd = getProductFromUser(pMarket, barcode);
			if (pProd != NULL) //This barcode exist in stock
				updateProductCount(pProd);
		}
	}
	else
		return 0;
	
	return 1;
}

int		addNewProduct(SuperMarket* pMarket)
{

	Product** pTempArr = (Product**)realloc(pMarket->productArr, (pMarket->productCount + 1) * sizeof(Product*));
	if (!pTempArr)
	{
		freeProducts(pMarket);
		return 0;
	}
	pMarket->productArr = pTempArr;
	
	Product* pProd = (Product*)calloc(1, sizeof(Product));
	if (!pProd)
	{
		free(pMarket->productArr);
		return 0;
	}

	initProductNoBarcode(pProd);

	do
	{
		generateBarcode(pProd);
	} while (!isBarcodeUnique(pMarket, pProd->barcode)); //generate new barcode until it is unique
	
	pMarket->productArr[pMarket->productCount] = pProd;
	pMarket->productCount++;
	pMarket->sortType = 0;
	return 1;
}

int		isBarcodeUnique(const SuperMarket* pMarket, const char* barcode)
{
	for (int i = 0; i < pMarket->productCount; i++)
	{
		if (strcmp(pMarket->productArr[i]->barcode, barcode) == 0)
			return 0; // Barcode is not unique
	}
	return 1; // Barcode is unique
}

int isCustomerIdUnique(const SuperMarket* pMarket, const char* id)
{
	for (int i = 0; i < pMarket->customerCount; i++)
	{
		if (strcmp(pMarket->customerArr[i].id, id) == 0)
		{
			printf("ID %s is not unique\n", id);
			return 0; // ID is not unique
		}
	}
	return 1; // ID is unique
}

int getChoiceIfMember() {
	int choice = -1;
	printf("Is the customer a club member? 1 for yes, 0 for no:\n");
	while (choice != 1 && choice != 0) {
		scanf("%d", &choice);
		if (choice != 1 && choice != 0)
			printf("Invalid input, please enter 1 for yes, 0 for no:\n");
	}
	return choice;
}



int		addCustomer(SuperMarket* pMarket)
{
	int choice = getChoiceIfMember();
	Customer cust;
	do {
		if (choice == 1) {
			if (!initMember(&cust)) return 0;
		}
		else {
			if (!initCustomer(&cust)) return 0;
		}
	} while (!isCustomerIdUnique(pMarket, cust.id));
	if (isCustomerInMarket(pMarket, &cust))
	{
		printf("This customer already in market\n");
		free(cust.name);
		return 0;
	}
	pMarket->customerArr = (Customer*)safeRealloc(pMarket->customerArr, (pMarket->customerCount + 1) * sizeof(Customer));
	if (!pMarket->customerArr)
	{
		free(cust.name);
		return 0;
	}
	pMarket->customerArr[pMarket->customerCount] = cust;
	pMarket->customerCount++;
	return 1;
}

int		isCustomerInMarket(SuperMarket* pMarket, Customer* pCust)
{
	for (int i = 0; i < pMarket->customerCount; i++)
	{
		if (strcmp(pMarket->customerArr[i].name, pCust->name) == 0)
			return 1;
	}
	return 0;
}

int	doShopping(SuperMarket* pMarket)
{
	Customer* pCustomer = getCustomerShopPay(pMarket);
	if (!pCustomer)
		return 0;

	if (pCustomer->pCart == NULL)
	{
		pCustomer->pCart = (ShoppingCart*)malloc(sizeof(ShoppingCart));
		if (!pCustomer->pCart)
			return 0;
		initCart(pCustomer->pCart);
	}
	fillCart(pMarket, pCustomer->pCart);
	if (pCustomer->pCart == NULL) //did not buy any thing
	{
		free(pCustomer->pCart);
		pCustomer->pCart = NULL;
	}
	printf("---------- Shopping ended ----------\n");
	return 1;
}

Customer*	doPrintCart(SuperMarket* pMarket)
{
	Customer* pCustomer = getCustomerShopPay(pMarket);
	if (!pCustomer)
		return NULL;
	if (pCustomer->pCart == NULL)
	{
		printf("Customer cart is empty\n");
		return NULL;
	}
	pCustomer->table.price(pCustomer, printShoppingCart(pCustomer->pCart));
	return pCustomer;
}

int	manageShoppingCart(SuperMarket* pMarket)
{
	Customer* pCustomer = doPrintCart(pMarket);
	char answer;

	if(!pCustomer)
		return 0;

	printf("Do you want to pay for the cart? y/Y, anything else to cancel shopping!\t");
	do {
		scanf("%c", &answer);
	} while (isspace(answer));

	getchar(); //clean the enter

	if (answer == 'y' || answer == 'Y')
		pay(pCustomer);
	else {
		clearCart(pMarket, pCustomer);
		cancelShopping(pCustomer);
	}
	return 1;

}

Customer*	getCustomerShopPay(SuperMarket* pMarket)
{
	if (pMarket->customerCount == 0)
	{
		printf("No customer listed to market\n");
		return NULL;
	}

	if (pMarket->productCount == 0)
	{
		printf("No products in market - cannot shop\n");
		return NULL;
	}

	Customer* pCustomer = getCustomerWhoShop(pMarket);
	if (!pCustomer)
	{
		printf("this customer not listed\n");
		return NULL;
	}

	return pCustomer;
}

void	printAllProducts(const SuperMarket* pMarket)
{
	printf("There are %d products\n", pMarket->productCount);
	printf("%-20s %-10s\t", "Name", "Barcode");
	printf("%-20s %-10s %-20s %-15s\n", "Type", "Price", "Count In Stoke", "Expiry Date");
	printf("-------------------------------------------------------------------------------------------------\n");

	generalArrayFunction(pMarket->productArr, pMarket->productCount, sizeof(Product*), printProduct);
}

void	printAllCustomers(const SuperMarket* pMarket)
{
	printf("There are %d listed customers\n", pMarket->customerCount);
	for (int i = 0; i < pMarket->customerCount; i++)
		pMarket->customerArr[i].table.print(&pMarket->customerArr[i]);
}


Customer* getCustomerWhoShop(SuperMarket* pMarket)
{
	printAllCustomers(pMarket);
	char searchTerm[MAX_STR_LEN];
	getsStrFixSize(searchTerm, sizeof(searchTerm), "Who is shopping? Enter customer id\n");

	Customer* pCustomer = FindCustomerById(pMarket, searchTerm);
	
	return pCustomer;
}


void fillCart(SuperMarket* pMarket, ShoppingCart* pCart)
{
	printAllProducts(pMarket);
	char op;
	while (1)
	{
		printf("Do you want to shop for a product? y/Y, anything else to exit!!\t");
		do {
			scanf("%c", &op);
		} while (isspace(op));
		getchar(); //clean the enter
		if (op != 'y' && op != 'Y')
			break;
		int count;
		Product* pProd = getProductAndCount(pMarket, &count);
		if(pProd)
		{
			if (!addItemToCart(pCart, pProd->barcode, pProd->price, count))
			{
				printf("Error adding item\n");
				return;
			}
			pProd->count -= count; //item bought!!!
		}
	}
}

//restore
void clearCart(SuperMarket* pMarket, Customer* pCustomer)
{
	if (pCustomer->pCart == NULL)
		return;

	NODE* pNode = pCustomer->pCart->itemLList.head.next;
	ShoppingItem* pItem;
	while(pNode != NULL) {
		pItem = pNode->key;
		Product* pProd = getProductByBarcode(pMarket, pItem->barcode);
		if (pProd)
			pProd->count += pItem->count;
		pNode = pNode->next;
	}
}

Product* getProductAndCount(SuperMarket* pMarket, int* pCount)
{
	char barcode[BARCODE_LENGTH + 1];
	Product* pProd = getProductFromUser(pMarket, barcode);
	if (pProd == NULL)
	{
		printf("No such product\n");
		return NULL;
	} 
	
	if (pProd->count == 0)
	{
		printf("This product out of stock\n");
		return NULL;
	}
	
	int count;
	do {
		printf("How many items do you want? max %d\n", pProd->count);
		scanf("%d", &count);
	} while (count <= 0 || count > pProd->count);
	*pCount = count;
	return pProd;
}

void	printProductByType(SuperMarket* pMarket)
{
	if (pMarket->productCount == 0)
	{
		printf("No products in market\n");
		return;
	}
	eProductType	type = getProductType();
	int count = 0;
	for (int i = 0; i < pMarket->productCount; i++)
	{
		if (pMarket->productArr[i]->type == type)
		{
			count++;
			printProduct(&pMarket->productArr[i]);
		}
	}
	if (count == 0)
		printf("There are no product of type %s in market %s\n", getProductTypeStr(type), pMarket->name);
}

Product* getProductFromUser(SuperMarket* pMarket, char* barcode)
{
	getBarcodeCode(barcode);
	Product* pProd = getProductByBarcode(pMarket, barcode);
	if (!pProd)
	{
		printf("No such product barcode\n");
		return NULL;
	}
	return pProd;
}

void	freeMarket(SuperMarket* pMarket)
{
	free(pMarket->name);
	freeProducts(pMarket);
	freeCustomers(pMarket);
}

void freeProducts(SuperMarket* pMarket)
{
	for (int i = 0; i < pMarket->productCount; i++)
	{
		freeProduct(pMarket->productArr[i]);
		free(pMarket->productArr[i]);
	}
	free(pMarket->productArr);
}

void freeCustomers(SuperMarket* pMarket)
{
	for (int i = 0; i < pMarket->customerCount; i++)
		freeCustomer(&pMarket->customerArr[i]);
	free(pMarket->customerArr);
}

int writeArrCustomers(const char* fileName, const Customer* customerArr, int amountCustomers) {
	FILE* fp = fopen(fileName, "w");
	if(!fp) {
		printf("Error open customers file to write\n");
		return 0;
	}
	fprintf(fp,"%d\n",amountCustomers);
	for (int i = 0; i < amountCustomers; i++) {
		customerArr[i].table.write(fp, &customerArr[i]);
	}
	fclose(fp);
	return 1;
}

int readCustomers(const char* fileName, SuperMarket* pMarket) {
	FILE* fp = fopen(fileName, "r");
	if(!fp) {
		printf("Error open customers file\n");
		return 0;
	}
	int amount;
	if (fscanf(fp, "%d\n", &amount) != 1)
		return 0;
	pMarket->customerArr = (Customer*)malloc(amount * sizeof(Customer));
	if(!pMarket->customerArr) {
		fclose(fp);
	}
	if(readArrCustomers(fp, pMarket, amount) != 1) {
		freeCustomers(pMarket);
		fclose(fp);
		return 0;
	}
	fclose(fp);
	return 1;
}

int readArrCustomers(FILE* fp, SuperMarket* pMarket, int amount) {
	int isMember = 0;
	for (int i = 0; i < amount; i++) {
		if (!readCustomer(fp, &pMarket->customerArr[i]) || fscanf(fp, "%d ", &isMember) != 1)
			return 0;

		if(isMember == 1) {
			if(readMember(fp, &pMarket->customerArr[i]) != 1)
				return 0;
		}
		else { //the other zero for mouth of regular customer
			if(fscanf(fp, "%d ", &isMember) != 1) {
				return 0;
			}
		}
		pMarket->customerCount++;
	}
	fclose(fp);
	return 1;
}


int	writeSuperMarket(const char* fileName, const SuperMarket* pMarket) {
	FILE* fp = fopen(fileName, "wb");
	if(!fp) {
		//message
		printf("Error open company file to write\n");
		return 0;
	}
	int lenSuperName = (int)strlen(pMarket->name) + 1;
	if(fwrite(&lenSuperName, sizeof(int), 1, fp)!= 1 ||
		fwrite(pMarket->name, sizeof(char), lenSuperName, fp)!= lenSuperName ||
		fwrite(&pMarket->productCount, sizeof(int), 1, fp) != 1) {
		fclose(fp);
		return 0;
	}
	if (writeProductsArr(fp, pMarket->productArr, pMarket->productCount)!= 1) {
		fclose(fp);
		return 0;
	}
	fclose(fp);
	return 1;
}


int writeProductsArr(FILE* fp, Product** pProdArr, int prodAmount) {
	for (int i = 0; i < prodAmount; i++) {
		if (writeProduct(fp, pProdArr[i]) != 1)
			return 0;
	}
	return 1;
}

int readSuperMarket(const char* fileName, SuperMarket* pMarket) {
	FILE* fp = fopen(fileName, "rb");
	if(!fp) {
		//message
		printf("Error open company file\n");
		return 0;
	}
	int lenSuperName;
	if(fread(&lenSuperName, sizeof(int), 1, fp) != 1) {
		fclose(fp);
		return 0;
	}
	pMarket->name = (char*)malloc(lenSuperName * sizeof(char));
	if(!pMarket->name) {
		fclose(fp);
		return 0;
	}

	if(fread(pMarket->name, sizeof(char), lenSuperName, fp) != lenSuperName) {
		free(pMarket->name);
		fclose(fp);
		return 0;
	}
	if(readProducts(fp, pMarket) != 1) {
		free(pMarket->name);
		fclose(fp);
	}

	fclose(fp);
	return 1;
}

int readProducts(FILE* fp, SuperMarket* pMarket) {
	int amountProd;
	if (fread(&amountProd, sizeof(int), 1, fp) != 1)
		return 0;

	pMarket->productArr = (Product**)malloc(amountProd * sizeof(Product*));
	if(!pMarket->productArr)
		return 0;

	if(readProductArr(fp, pMarket->productArr, &pMarket->productCount, amountProd) !=  1) {
		freeProducts(pMarket);
		return 0;
	}
	fclose(fp);
	return 1;
}


int readProductArr(FILE* fp, Product** pProdArr, int* pProdArrAmount, int amount) {
	for (int i = 0; i < amount; i++) {
		Product* newProduct = (Product*)malloc(sizeof(Product));
		if(!newProduct || readProduct(fp, newProduct) != 1)
			return 0;
		pProdArr[i] = newProduct;
		(*pProdArrAmount)++;
	}
	return 1;
}

void writeEverything(const SuperMarket* pMarket) {
	if(writeSuperMarket("SuperMarket.bin", pMarket) != 1||
		writeArrCustomers("Customers.txt", pMarket->customerArr, pMarket->customerCount) != 1) {
		printf("Error to write\n");
		return;
	}
	printf("Success to write\n");
}

void	getUniquBarcode(char* barcode, SuperMarket* pMarket)
{
	int cont = 1;
	while (cont)
	{
		getBarcodeCode(barcode);
		int index = getProductIndexByBarcode(pMarket, barcode);
		if (index == -1)
			cont = 0;
		else
			printf("This product already in market\n");
	}
}

int getProductIndexByBarcode(SuperMarket* pMarket, const char* barcode)
{
	for (int i = 0; i < pMarket->productCount; i++)
	{
		if (isProduct(pMarket->productArr[i], barcode))
			return i;
	}
	return -1;
}

Product* getProductByBarcode(SuperMarket* pMarket, const char* barcode)
{
	for (int i = 0; i < pMarket->productCount; i++)
	{
		if (isProduct(pMarket->productArr[i], barcode))
			return pMarket->productArr[i];
	}
	return NULL;

}

Customer* FindCustomerByName(SuperMarket* pMarket, const char* name)
{
	for (int i = 0; i < pMarket->customerCount; i++)
	{
		if (isCustomer(&pMarket->customerArr[i], name))
			return &pMarket->customerArr[i];
	}
	return  NULL;
}

Customer* FindCustomerById(SuperMarket* pMarket, const char* id)
{
	for (int i = 0; i < pMarket->customerCount; i++)
	{
		if (isCustomerById(&pMarket->customerArr[i], id))
			return &pMarket->customerArr[i];
	}
	return  NULL;
}

void printSortOptions() {
	printf("Base on what field do you want to sort?\n");
	for (int i = 1; i < eNofProductType; i++) {
		printf("Enter %d for %s\n", i, sortTypes[i]);
	}
}

void sortProducts(SuperMarket* pMarket) {
	int st, stop = 0;
	do {
		printSortOptions();
		scanf("%d", &st);
		switch (st) {
			case eUnSorted:
				printf("Error in sorting\n");
				stop = 1;
				break;

			case eSPName:
				qsort(pMarket->productArr, pMarket->productCount, sizeof(Product*), compareProductByName);
				pMarket->sortType = 1;
				stop = 1;
				break;

			case eSPCount:
				qsort(pMarket->productArr, pMarket->productCount, sizeof(Product*), compareProductByCount);
				pMarket->sortType = 2;
				stop = 1;
				break;

			case eSPPrice:
				qsort(pMarket->productArr, pMarket->productCount, sizeof(Product*), compareProductByPrice);
				pMarket->sortType = 3;
				stop = 1;
				break;

			case eNofSortTypes:
				printf("Error in sorting\n");
				stop = 1;
				break;
		}
	}while (!stop);
}

void searchProduct(const SuperMarket* pMarket) {
	if(pMarket->sortType == eUnSorted) {
		printf("The search cannot be performed, array not sorted\n");
		return;
	}
	Product** pProduct = NULL;
	Product temp;
	Product* ptrProducttemp = &temp;
	printf("Enter product %s\n", sortTypes[pMarket->sortType]);
	switch (pMarket->sortType) {

		case eSPName:
			scanf("%s", ptrProducttemp->name);
			pProduct = (Product**)bsearch(&ptrProducttemp, pMarket->productArr,
				pMarket->productCount,sizeof(Product*), compareProductByName);
			break;

		case eSPCount:
			scanf("%d", &ptrProducttemp->count);
			pProduct = (Product**)bsearch(&ptrProducttemp, pMarket->productArr,
				pMarket->productCount,sizeof(Product*), compareProductByCount);
			break;

		case eSPPrice:
			scanf("%f", &ptrProducttemp->price);
			pProduct = (Product**)bsearch(&ptrProducttemp, pMarket->productArr,
				pMarket->productCount,sizeof(Product*), compareProductByPrice);
			break;
	}

	if(!pProduct) {
		printf("Product not found\n");
		return;
	}
	printf("Product found\n");
	printProduct(pProduct);
}


