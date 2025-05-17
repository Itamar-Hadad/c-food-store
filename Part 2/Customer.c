#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "Customer.h"
#include "General.h"

int	initCustomer(Customer* pCustomer)
{
	char firstName[MAX_STR_LEN];
	char lastName[MAX_STR_LEN];

	char* parts[2] = { firstName,lastName };
	char* msgParts[2] = { "Enter customer first name\n" ,"Enter customer last name\n" };
	for(int i = 0; i < 2; i++)
	{ 
		getNamePart(parts[i], msgParts[i]);
		upperLowerCustomerName(parts[i]);
	}

	char* combineName = combineFirstLast(parts);
	if (!combineName)
		return 0;

	pCustomer->name = combineName;

	char msg[MAX_STR_LEN];
	sprintf(msg, "ID should be %d digits\n"
		"For example: 123456789\n", CUSTOMER_ID_LENGTH);
	do {
		pCustomer->id = getStrExactLength(msg);
		if (!pCustomer->id)
			return 0;
	} while (!isCustomerIdValid(pCustomer->id));

	pCustomer->pCart = NULL;
	pCustomer->derivedObj = NULL;
	initVTableCustomer(pCustomer);
	return 1;
}

void	getNamePart(char* part, const char* msg)
{
	int ok = 0;
	do {
		getsStrFixSize(part, MAX_STR_LEN, msg);
		if (checkEmptyString(part))
			printf("Name cound not be empty\n");
		else if (!checkAlphaSpaceStr(part))
			printf("Name should contain only letters\n");
		else
			ok = 1;
	} while (!ok);
}

void	upperLowerCustomerName(char* name)
{
	toLowerStr(name);
	while (isspace(*name))
		name++;

	*name = toupper(*name);
}

char* combineFirstLast(char** parts)
{
	char temp[MAX_STR_LEN * 2] = { 0 };
	char** pNameParts = NULL;
	int count = 0;
	size_t totalLength = 0;

	for (int i = 0; i < 2; i++)
	{
		pNameParts = splitCharsToWords(parts[i], &count, NAMES_SEP, &totalLength);
		if (!pNameParts)
			return NULL;

		for (int j = 0; j < count; j++)
		{
			strcat(temp, pNameParts[j]);
			strcat(temp, NAMES_SEP);
			free(pNameParts[j]); //do not need
		}
		free(pNameParts);
		pNameParts = NULL;

		if (i == 0)
			strcat(temp, NAME_PARTS_SEP);
	}
	temp[strlen(temp) - 1] = '\0'; //remove last space
	
	char* combineName = myStrDup(temp);
	return combineName;
}

void initVTableCustomer(Customer* pCustomer) {
	pCustomer->table.print = printCustomer;
	pCustomer->table.price = printTotalPriceCustomer;
	pCustomer->table.free = freeCustomer;
	pCustomer->table.write = writeCustomer;

}

void printCustomer(const Customer* pCustomer)
{
	printf("Name: %s\n", pCustomer->name);
	printf("ID: %s\n", pCustomer->id);

	if (pCustomer->pCart == NULL)
		printf("Shopping cart is empty!\n");
	else
	{
		printf("Doing shopping now!!!\n");
	}
}

int isCustomerIdValid(const char* id)
{
	if (strlen(id) != CUSTOMER_ID_LENGTH)
		return 0;
	for (int i = 0; i < CUSTOMER_ID_LENGTH; i++)
	{
		if (!isdigit(id[i]))
			return 0;
	}
	return 1;
}

void printTotalPriceCustomer(const Customer* pCustomer, float price) {
	printf("Total price for %s is %.2f\n", pCustomer->name, price);
}

void pay(Customer* pCustomer)
{
	if (!pCustomer->pCart)
		return;

	printf("---------- Cart info and bill for %s ----------\n", pCustomer->name);
	pCustomer->table.price(pCustomer, printShoppingCart(pCustomer->pCart));
	printf("!!! --- Payment was recived!!!! --- \n");
	freeShoppingCart(pCustomer->pCart);
	free(pCustomer->pCart);
	pCustomer->pCart = NULL;
}

void cancelShopping(Customer* pCustomer)
{
	if (!pCustomer->pCart)
		return;
	printf("!!! --- Purchase was canceled!!!! --- \n");
	freeShoppingCart(pCustomer->pCart);
	free(pCustomer->pCart);
	pCustomer->pCart = NULL;
}


int	isCustomerById(const Customer* pCust, const char* id)
{
	if (strcmp(pCust->id, id) == 0)
		return 1;
	return 0;
}

int	isCustomer(const Customer* pCust, const char* name)
{
	if (strcmp(pCust->name, name) == 0)
		return 1;
	return 0;
}

void freeCustomer(Customer* pCust)
{
	if (pCust->pCart)
		pay(pCust); //will free every thing
	free(pCust->name);
	free(pCust->id);
}

void writeCustomer(FILE* fp, const Customer* pCust) {
	fprintf(fp,"%s\n%s\n0 0\n", pCust->name, pCust->id);
}

int readCustomer(FILE* fp, Customer* pCust) {
	char temp[MAX_STR_LEN] = {0};
	myGetsFile(temp, MAX_STR_LEN, fp);
	pCust->id = (char*)malloc((CUSTOMER_ID_LENGTH + 1) * sizeof(char));
	if(!pCust->id)
		return 0;
	if(fscanf(fp, "%s", pCust->id) != 1) {
		free(pCust->id);
		return 0;
	}
	pCust->name = (char*)malloc((strlen(temp) + 1)*sizeof(char));
	if(!pCust->name) {
		free(pCust->id);
		return 0;
	}
	strcpy(pCust->name, temp);
	pCust->derivedObj = NULL;
	pCust->pCart = NULL;
	initVTableCustomer(pCust);
	return 1;
}

