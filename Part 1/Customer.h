#define _CRT_SECURE_NO_WARNINGS
#ifndef __CUSTOMER__
#define __CUSTOMER__
#include "ShoppingCart.h"

#define ID_SIZE 9
#define NAME_SEP " - "

typedef struct
{
    char id[ID_SIZE + 1];//+1 for '/0'
    char* name;
    ShoppingCart* shoppingCart;
} Customer;

int initCustomer(Customer* customer);
int initName(Customer* customer);
int checkIfLetters(const char* name);
void capitalizeFirstLetter(char* str);
void initId(Customer* customer);
int validId(const char* str);
void freeCustomer(Customer* customer);
void showCustomer(const Customer* customer);
#endif