#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "VTable.h"
#include "ShoppingCart.h"

#define CUSTOMER_ID_LENGTH 9
#define NAMES_SEP " "
#define NAME_PARTS_SEP "- "

typedef struct _Customer
{
	char*			id;
	char*			name;
	void*			derivedObj;
	VTable			table;
	ShoppingCart*	pCart;


}Customer;

int		initCustomer(Customer* pCustomer);
void	printCustomer(const Customer* pCustomer);

int		isCustomerIdValid(const char* id);

int		isCustomer(const Customer* pCust, const char* name);
int		isCustomerById(const Customer* pCust, const char* id);
//int		isCustomersNameValid(const char* name);
void	getNamePart(char* part, const char* msg);
void	upperLowerCustomerName(char* name);
//char*	combineFirstLast(char*  firstName, char* lastName);
char*	combineFirstLast(char** parts);

void initVTableCustomer(Customer* pCustomer);

void	printTotalPriceCustomer(const Customer* pCustomer, float price);
void	pay(Customer* pCustomer);
void	cancelShopping(Customer* pCustomer);

void	freeCustomer(Customer* pCust);

void writeCustomer(FILE* fp, const Customer* pCust);
int readCustomer(FILE* fp, Customer* pCust);

