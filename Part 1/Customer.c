#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include "Customer.h"

int initCustomer(Customer* customer)
{
    if (!initName(customer))
        return 0;
    initId(customer);
    customer->shoppingCart = NULL;
    return 1;
}


int initName(Customer* customer)
{
    char temp[MAX_LENGTH], * name;
    int sizeName;
    do {
        printf("Enter customer first name:\n");
        myGets(temp, MAX_LENGTH);
    } while (!checkIfLetters(temp));
    removeExtraSpaces(temp);
    name = _strdup(temp);
    if (!name)
        return 0;
    capitalizeFirstLetter(name);
    do {
        printf("Enter customer last name:\n");
        myGets(temp, MAX_LENGTH);
    } while (!checkIfLetters(temp));
    removeExtraSpaces(temp);
    capitalizeFirstLetter(temp);
    sizeName = (int)(strlen(name) + strlen(temp) + 4); // strlen returns size_t
    name = (char*)safeRealloc(name, sizeName * sizeof(char));
    if (!name)
        return 0;
    strcat(name, NAME_SEP);
    strcat(name, temp);
    customer->name = name;
    return 1;
}

int checkIfLetters(const char* name) {
    for (int i = 0; i < strlen(name); i++)
    {
        if (!isalpha(name[i]) && name[i] != ' ') {
            printf("Name should contain only letters\n");
            return 0;
        }
    }
    return 1;
}

void capitalizeFirstLetter(char* str)
{
    // Ensure the string is not empty
    if (str == NULL || strlen(str) == 0)
        return;

    // Convert the first character to uppercase
    str[0] = toupper(str[0]);

    // Convert all other characters to lowercase
    for (int i = 1; str[i] != '\0'; i++)
        str[i] = tolower(str[i]);

}

void initId(Customer* customer)
{
    char temp[MAX_LENGTH];
    printf("Enter customer Id:\n");
    do {
        printf("ID should be 9 digits\n");
        printf("For example: 123456789\n");
        scanf("%s", temp);
    } while (!validId(temp));
    strcpy(customer->id, temp);
}

int validId(const char* str) {
    if (strlen(str) > ID_SIZE)
        return 0;
    for (int i = 0; i < strlen(str); ++i) {
        if (!isdigit(str[i]))
            return 0;
    }
    return 1;
}

void freeCustomer(Customer* customer) {
    free(customer->name);
    freeCart(customer->shoppingCart);
}

void showCustomer(const Customer* customer) {
    printf("Name: %s\n", customer->name);
    printf("ID: %s\n", customer->id);
    if (!customer->shoppingCart)
        printf("Shopping cart is empty!\n");
    else
        printf("Doing shopping now!!!\n");
}