#define _CRT_SECURE_NO_WARNINGS
#ifndef __PRODUCT__
#define __PRODUCT__
#include "generalFunctions.h"
#include "Date.h"

#define PNAME_SIZE 20
#define MIN_BARCODE 10000
#define MAX_BARCODE 99999



typedef enum { eFV, eFR, eFZ, eSH, eNofType } Type;

typedef struct
{
    char name[PNAME_SIZE + 1]; //+ 1 for '/0'
    char barcode[BARCODE_SIZE + 1]; //+1 for '/0'
    Type type;
    float price;
    int amount;
    Date date;

} Product;
void initProduct(Product* product);
void initNameProduct(Product* product);
void initProductType(Product* product);
int getType();
const char* getTypeName(int nType);
void initBarcode(Product* product);
void initPrice(Product* product);
void initAmount(Product* product);
void increaseAmount(Product* product);
int decreaseAmount(Product* product);
int verifyBarcodeStructure(const char* barcode);
void showProduct(const Product* product);
void printProductBarcodeRules();

#endif