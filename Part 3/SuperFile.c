#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "General.h"
#include "FileHelper.h"
#include "SuperFile.h"
#include "Product.h"
#include "myMacros.h"



int	saveSuperMarketToFile(const SuperMarket* pMarket, const char* fileName,
	const char* customersFileName, int fComp)
{
	FILE* fp;
	fp = fopen(fileName, "wb");
	CHECK_MSG_RETURN_0(fp, "Error open supermarket file to write\n")


	if(fComp == 1) {
		if (!writeNameCount_Compress(pMarket->productCount, pMarket->name, fp))
			CLOSE_RETURN_0(fp)
	} else {
		if (!writeNameCount(pMarket, fp))
			CLOSE_RETURN_0(fp)

	}
	if(!writeMarketProducts(pMarket->productArr, pMarket->productCount, fp, fComp))
		CLOSE_RETURN_0(fp)

	fclose(fp);
	saveCustomersToTextFile(pMarket->customerArr, pMarket->customerCount, customersFileName);
	return 1;
}

int writeNameCount(const SuperMarket* pMarket, FILE* fp) {
	if (!writeStringToFile(pMarket->name, fp, "Error write supermarket name\n"))
		return 0;
	if (!writeIntToFile(pMarket->productCount, fp, "Error write product count\n"))
		return 0;
	return 1;
}

int writeNameCount_Compress(int pCount, const char* superName, FILE* fp) {
	BYTE temp[2];
	temp[0] = pCount >> 2;
	temp[1] = pCount << 6;
	int nameSize = (int)strlen(superName);
	temp[1] |= nameSize;
	if(fwrite(temp, sizeof(BYTE), 2, fp) != 2) {
		printf("Error write product's amount and name market length\n");
		return 0;
	}

	if(fwrite(superName, sizeof(char), nameSize, fp) != nameSize){
		printf("Error write supermarket name\n");
		return 0;
	}
	return 1;
}

int writeMarketProducts(const Product** productArr, int productCount, FILE* fp, int fComp) {
	for (int i = 0; i < productCount; i++) {
		if(fComp == 1) {
			if (!saveProductToFile_Compress(productArr[i], fp))
				return 0;
		} else {
			if (!saveProductToFile(productArr[i], fp))
				return 0;
		}
	}
	return 1;
}



int saveProductToFile_Compress(const Product* pProduct, FILE* fp) {
	if (!writeNameBarcodeProduct_Comp(pProduct,fp))
		return 0;
	if (!writeAmountPriceProduct_Comp(pProduct, fp))
		return 0;
	if (!saveDateToFileComp(&pProduct->expiryDate, fp))
		return 0;
	return 1;
}


int	loadSuperMarketFromFile(SuperMarket* pMarket, const char* fileName,
	const char* customersFileName, int fComp)
{
	FILE* fp;
	fp = fopen(fileName, "rb");
	CHECK_MSG_RETURN_0(fp, "Error open company file\n")

	int count;

	if(fComp == 1) {
		if (!readNameCount_Compress(pMarket, fp, &count))
			return 0;
	} else {
		if (!readNameCount(pMarket, fp, &count))
			CLOSE_RETURN_0(fp)
	}
	if(!loadProdutsToMarket(pMarket, fp, fComp, count))
		FREE_CLOSE_FILE_RETURN_0(pMarket->name, fp)
	fclose(fp);
	pMarket->customerArr = loadCustomersFromTextFile(customersFileName, &pMarket->customerCount);
	if (!pMarket->customerArr)
		return 0;
	return	1;
}

int loadProdutsToMarket(SuperMarket* pMarket, FILE* fp, int fComp, int count) {
	pMarket->productArr = (Product**)malloc(count * sizeof(Product*));
	CHECK_RETURN_0(pMarket->productArr)

	for (int i = 0; i < count; i++)
	{
		pMarket->productArr[i] = (Product*)malloc(sizeof(Product));
		if (!pMarket->productArr[i])
		{
			freeProducts(pMarket);
			return 0;
		}
		if(fComp == 1) {
			if (!loadProductsToMarket_Compress(pMarket->productArr[i], fp)){
				free(pMarket->productArr[i]);
				freeProducts(pMarket);
				return 0;
			}
		} else {
			if (!loadProductFromFile(pMarket->productArr[i], fp)) {
				free(pMarket->productArr[i]);
				freeProducts(pMarket);
				return 0;
			}
		}
		pMarket->productCount++;
	}
	return 1;
}



int readNameCount(SuperMarket* pMarket, FILE* fp, int* count) {
	pMarket->name = readStringFromFile(fp, "Error reading supermarket name\n");
	CHECK_RETURN_0(pMarket->name)

	if (!readIntFromFile(count, fp, "Error reading product count\n"))
	{
		FREE_CLOSE_FILE_RETURN_0(pMarket->name, fp)
	}
	return 1;
}

int readNameCount_Compress(SuperMarket* pMarket,FILE* fp, int* count) {
	BYTE temp[2];
	if(fread(temp, sizeof(BYTE), 2, fp) != 2) {
		printf("Error read product's amount and name market length\n");
		return 0;
	}
	*count = (temp[0] & 0xFF) << 2 | (temp[1] >> 6 & 0x3);
	int nameSize = temp[1] & 0x3F;
	pMarket->name = (char*)calloc((nameSize + 1), sizeof(char));
	if(!pMarket->name) {
		printf("Error allocate name memory\n");
		return 0;
	}
	if(fread(pMarket->name, sizeof(char), nameSize, fp) != nameSize) {
		free(pMarket->name);
		pMarket->name = NULL;
		printf("Error read supermarket name\n");
		return 0;
	}
	return 1;
}


int loadProductsToMarket_Compress(Product* product, FILE* fp) {
	if (!readNameBarcodeProduct_Comp(product,fp))
		return 0;
	if (!readAmountPriceProduct_Comp(product, fp))
		return 0;
	if(!loadDatefromFileComp(&product->expiryDate, fp))
		return 0;
	return 1;
}


int	saveCustomersToTextFile(const Customer* customerArr, int customerCount, const char* customersFileName)
{
	FILE* fp;

	fp = fopen(customersFileName, "w");
	CHECK_MSG_RETURN_0(fp, "Error opening customers file to write\n")

	fprintf(fp, "%d\n", customerCount);
	for (int i = 0; i < customerCount; i++)
		customerArr[i].vTable.saveToFile(&customerArr[i], fp);

	fclose(fp);
	return 1;
}

Customer* loadCustomersFromTextFile(const char* customersFileName, int* pCount)
{
	FILE* fp;

	fp = fopen(customersFileName, "r");
	if (!fp) {
		printf("Error open customers file to write\n");
		return NULL;
	}

	Customer* customerArr = NULL;
	int customerCount;

	fscanf(fp, "%d\n", &customerCount);

	if (customerCount > 0)
	{
		customerArr = (Customer*)calloc(customerCount, sizeof(Customer)); //cart will be NULL!!!
		if (!customerArr)
		{
			fclose(fp);
			return NULL;
		}

		for (int i = 0; i < customerCount; i++)
		{
			if (!loadCustomerFromFile(&customerArr[i], fp))
			{
				freeCustomerCloseFile(customerArr, i, fp);
				return NULL;
			}
		}
	}

	fclose(fp);
	*pCount = customerCount;
	return customerArr;
}


void freeCustomerCloseFile(Customer* customerArr, int count, FILE* fp)
{
	for (int i = 0; i < count; i++)
	{
		free(customerArr[i].name);
		customerArr[i].name = NULL;
		if (customerArr[i].pDerivedObj)
		{
			free(customerArr[i].pDerivedObj);
			customerArr[i].pDerivedObj = NULL;
		}
	}
	free(customerArr);
	fclose(fp);
}