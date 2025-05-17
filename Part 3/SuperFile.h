#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include <stdio.h>
#include "Supermarket.h"
#include "Customer.h"

int		saveSuperMarketToFile(const SuperMarket* pMarket, const char* fileName,
	const char* customersFileName, int fComp);

int		writeNameCount_Compress(int pCount, const char* superName, FILE* fp);
int		writeNameCount(const SuperMarket* pMarket, FILE* fp);

int		writeMarketProducts(const Product** productArr, int productCount, FILE* fp, int fComp);
int		saveProductToFile_Compress(const Product* pProduct, FILE* fp);

int		loadProdutsToMarket(SuperMarket* pMarket, FILE* fp,int fConp, int count);
int		loadProductsToMarket_Compress(Product* product, FILE* fp);

int		readNameCount(SuperMarket* pMarket, FILE* fp, int* count);
int		readNameCount_Compress(SuperMarket* pMarket,FILE* fp, int* count);

int		loadSuperMarketFromFile(SuperMarket* pMarket, const char* fileName,
	const char* customersFileName, int fComp);

int		saveCustomersToTextFile(const Customer* customerArr, int customerCount,
	const char* customersFileName);
Customer* loadCustomersFromTextFile(const char* customersFileName, int* pCount);
void		freeCustomerCloseFile(Customer* customerArr, int customerIndex, FILE* fp);

