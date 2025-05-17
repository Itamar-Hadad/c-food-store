#define _CRT_SECURE_NO_WARNINGS
#pragma once

#define EXIT -1
#define CUSTOMER_FILE_NAME "Customers.txt"
#define ON_EXIT(n) {printUsage(); system("pause"); return n;}

typedef enum
{
	eShowSuperMarket, eAddProduct, eAddCustomer, eCustomerDoShopping, ePrintCart, eCustomerManageShoppingCart,
	eSortProducts, eSearchProduct, ePrintProductByType, eNofOptions
} eMenuOptions;

const char* menuStrings[eNofOptions] = { "Show SuperMarket", "Add Product",
								"Add Customer", "Customer Shopping","Print Shopping Cart","Customer Shopping Cart Managment",
								"Sort Products", "Search Product", "Print Product By Type" };

int menu();
void printUsage();