#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "Customer.h"
#include "Product.h"
#include "ShoppingCart.h"

typedef enum {eUnSorted, eSPName, eSPCount, eSPPrice, eNofSortTypes} eSortTypes;

typedef struct
{
	char*		name;
	Customer*	customerArr;
	int			customerCount;
	Product**	productArr;
	int			productCount;
	eSortTypes	sortType;
}SuperMarket;

void		basicInitSuperMarket(SuperMarket* pMarket);
int			readFiles(SuperMarket* pMarket);
int			initSuperMarket(SuperMarket* pMarket);
void		printSuperMarket(const SuperMarket* pMarket);
int			addProduct(SuperMarket* pMarket);
int			addNewProduct(SuperMarket* pMarket);
int			getChoiceIfMember();
int			addCustomer(SuperMarket* pMarket);
int			isCustomerInMarket(SuperMarket* pMarket, Customer* pCust);
int			doShopping(SuperMarket* pMarket);
Customer*	doPrintCart(SuperMarket* pMarket);
int			manageShoppingCart(SuperMarket* pMarket);
Customer*	getCustomerShopPay(SuperMarket* pMarket);
void		fillCart(SuperMarket* pMarket, ShoppingCart* pCart);
void		clearCart(SuperMarket* pMarket, Customer* pCustomer);

void		printProductByType(SuperMarket* pMarket);
void		printAllProducts(const SuperMarket* pMarket);
void		printAllCustomers(const SuperMarket* pMarket);
int			isBarcodeUnique(const SuperMarket* pMarket, const char* barcode);
int 		isCustomerIdUnique(const SuperMarket* pMarket, const char* id);


int			getProductIndexByBarcode(SuperMarket* pMarket, const char* barcode);
Product*	getProductByBarcode(SuperMarket* pMarket, const char* barcode);
Product*	getProductFromUser(SuperMarket* pMarket, char* barcode);
void		getUniquBarcode(char* barcode, SuperMarket* pMarket);
Customer*	FindCustomerByName(SuperMarket* pMarket, const char* name);
Customer*	FindCustomerById(SuperMarket* pMarket, const char* id);

void		printSortOptions();
void		sortProducts(SuperMarket* pMarket);
void		searchProduct(const SuperMarket* pMarket);

Customer*	getCustomerWhoShop(SuperMarket* pMarket);
Product*	getProductAndCount(SuperMarket* pMarket, int* pCount);

void		freeMarket(SuperMarket* pMarket);
void		freeProducts(SuperMarket* pMarket);
void		freeCustomers(SuperMarket* pMarket);

int			writeArrCustomers(const char* fileName, const Customer* customerArr, int amountCustomers);
int			readCustomers(const char* fileName, SuperMarket* pMarket);
int			readArrCustomers(FILE* fp, SuperMarket* pMarket, int amount);

int			writeSuperMarket(const char* fileName, const SuperMarket* pMarket);
int			writeProductsArr(FILE* fp, Product** pProdArr, int prodAmount);

int			readSuperMarket(const char* fileName, SuperMarket* pMarket);
int			readProducts(FILE* fp, SuperMarket* pMarket);
int			readProductArr(FILE* fp, Product** pProdArr, int* pProdArrAmount, int amount);

void		writeEverything(const SuperMarket* pMarket);



