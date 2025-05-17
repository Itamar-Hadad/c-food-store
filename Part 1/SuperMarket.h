#define _CRT_SECURE_NO_WARNINGS
#ifndef __SUPERMARKET__
#define __SUPERMARKET__
#include "Customer.h"
#include "Product.h"

typedef struct
{
    char* marketName;
    Customer* customers;
    int customersAmount;
    Product** products;
    int productsAmount;
} SuperMarket;
int initMarket(SuperMarket* superMarket);
int initMarketName(SuperMarket* superMarket);
void showSuperMarket(const SuperMarket* superMarket);
void showProducts(const SuperMarket* superMarket);
void showCustomers(const SuperMarket* superMarket);
int addProduct(SuperMarket* superMarket);
int addNewProduct(SuperMarket* superMarket);
void freeAllOpenCarts(Customer* customers, int customersAmount);
void updateExistProduct(SuperMarket* superMarket);
int verifyUniqId(SuperMarket* superMarket, Customer* newCustomer);
int addCustomer(SuperMarket* superMarket);
Customer* getCustomer(const SuperMarket* superMarket, const char* tempID);
Customer* whoIsShopping(const SuperMarket* superMarket, int fBuy);
int checkBarcodeExist(const Product** products, int productsAmount, const char* tempBarcode, const Product** product);
Product* getProductToAdd(const Product** products, int productsAmount);
int addItemToCart(Customer* customer, const Product** products, int productsAmount);
int shoppingProcess(SuperMarket* superMarket);
int verifyShoppingProcessAllowed(const SuperMarket* superMarket);
int verifyListedCustomer(const Customer* customers, int customersAmount, const char* tempID);
void showCustomerCart(const SuperMarket* superMarket);
void customerCartManagment(SuperMarket* superMarket, Customer* customer);
void shoppingCartManagement(SuperMarket* superMarket);
void CartPayment(const Customer* customer);
void restoreCart(SuperMarket* superMarket, ShoppingCart* shoppingCart);
void showProductByType(const SuperMarket* superMarket);
void exitProgram(SuperMarket* supermarket);
void verifyNoOpenCarts(SuperMarket* superMarket);
void freeSuperMarket(SuperMarket* superMarket);
void freeProducts(Product** products, int productsAmount);
void freeCustomers(Customer* customers, int customersAmount);
#endif
