#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "SuperMarket.h"



int initMarket(SuperMarket* superMarket) { // first action on the execution
    if (!initMarketName(superMarket))
        return 0;
    superMarket->customers = NULL;
    superMarket->customersAmount = 0;
    superMarket->products = NULL;
    superMarket->productsAmount = 0;
    return 1;
}

int initMarketName(SuperMarket* superMarket) {
    char temp[MAX_LENGTH];
    printf("Enter market name:\n");
    myGets(temp, MAX_LENGTH);
    superMarket->marketName = _strdup(temp);
    if (!superMarket->marketName)
        return 0;
    return 1;
}

void showSuperMarket(const SuperMarket* superMarket) { // option 0
    printf("Super Market Name: %s\n", superMarket->marketName);
    showProducts(superMarket);
    showCustomers(superMarket);
}

//check if we can middle the stock in the middle
void showProducts(const SuperMarket* superMarket) {
    printf("There are %d products\n", superMarket->productsAmount);
    printf("%-20s%-10s%-20s%-10s%-20s%-15s\n",
        "Name", "Barcode", "Type", "Price", "Count In Stock", "Expiry Date");
    printf("-------------------------------------------------------------------------------------"
        "------------\n");
    for (int i = 0; i < superMarket->productsAmount; i++)
        showProduct(superMarket->products[i]);
}

void showCustomers(const SuperMarket* superMarket) {
    printf("\nThere are %d listed customers\n", superMarket->customersAmount);
    for (int i = 0; i < superMarket->customersAmount; i++)
        showCustomer(&superMarket->customers[i]);
}

int addProduct(SuperMarket* superMarket) { // option 1
    char ch;
    printf("\nAdding new product? y/Y: ");
    do {
        scanf("%c", &ch);
    } while (isspace(ch));
    if (ch == 'y' || ch == 'Y') {
        if (!addNewProduct(superMarket))
            return 0;
    }
    else
        updateExistProduct(superMarket);
    return 1;
}

int addNewProduct(SuperMarket* superMarket) {
    Product** temp;
    Product* newProduct = (Product*)malloc(sizeof(Product));
    if (!newProduct) {
        return 0;
    }
    initProduct(newProduct);
    temp = (Product**)realloc(superMarket->products, (superMarket->productsAmount + 1) * sizeof(Product*));
    if (!temp) {
        free(newProduct);
        freeProducts(superMarket->products, superMarket->productsAmount);
        /*
        Since we cannot allocate additional space in the array of product pointers,
        I need to free all the products in the products array, as well as the array itself.
        However, it may happen that there are open carts containing items based on the products
        we just deleted.
        Therefore, we need to release the customers' carts as well.
        .*/
        freeAllOpenCarts(superMarket->customers, superMarket->customersAmount);
        superMarket->products = NULL;
        superMarket->productsAmount = 0;
        return 0;
    }
    superMarket->products = temp;
    superMarket->products[superMarket->productsAmount] = newProduct;
    superMarket->productsAmount++;
    return 1;
}

void freeAllOpenCarts(Customer* customers, int customersAmount) {
    for (int i = 0; i < customersAmount; i++) {
        if (customers[i].shoppingCart != NULL) {
            freeCart(customers[i].shoppingCart);
            customers[i].shoppingCart = NULL;
        }
    }
}


void updateExistProduct(SuperMarket* superMarket) {
    char ch;
    if (!superMarket->products) {
        printf("Error adding product\n");
        return; //return to main menu
    }
    printf("Do you want to increase the amount of an existing product? y/Y: ");
    do {
        scanf("%c", &ch);
    } while (isspace(ch));
    if (ch == 'y' || ch == 'Y') {
        showProducts(superMarket);
        Product* existProduct = getProductToAdd(superMarket->products, superMarket->productsAmount);
        if (existProduct == NULL)
            return;
        increaseAmount(existProduct);
    }
}

int verifyUniqId(SuperMarket* superMarket, Customer* newCustomer) {
    int fUniqID = 0;
    while (!fUniqID)
    {
        if (!initCustomer(newCustomer)) //if we can't initname
            return 0;

        if (!verifyListedCustomer(superMarket->customers,
            superMarket->customersAmount, newCustomer->id))
            fUniqID = 1;
        if (!fUniqID)
            printf("ID %s is not unique\n", newCustomer->id);
    }
    return 1;
}

int addCustomer(SuperMarket* superMarket) { // option 2
    Customer newCustomer;
    Customer* temp;

    if (!verifyUniqId(superMarket, &newCustomer))
        return 0;
    temp = (Customer*)realloc(superMarket->customers,
        (superMarket->customersAmount + 1) * sizeof(Customer));
    if (!temp) {
        freeCustomers(superMarket->customers, superMarket->customersAmount);
        superMarket->customers = NULL;
        superMarket->customersAmount = 0;
        return 0;
    }
    superMarket->customers = temp;
    superMarket->customers[superMarket->customersAmount] = newCustomer;
    superMarket->customersAmount++;
    return 1;
}


Customer* getCustomer(const SuperMarket* superMarket, const char* tempID) {
    for (int i = 0; i < superMarket->customersAmount; i++) {
        if (strcmp(superMarket->customers[i].id, tempID) == 0)
            return &superMarket->customers[i];
    }
    return NULL;
}


Customer* whoIsShopping(const SuperMarket* superMarket, int fBuy) {
    char tempID[MAX_LENGTH];
    showCustomers(superMarket);
    if (fBuy == 1)
        printf("Who is shopping? Enter customer ID:\n");
    else
        printf("Who is buying? Enter customer ID:\n");
    do {
        scanf("%s", tempID);
    } while (!validId(tempID));
    Customer* customer = getCustomer(superMarket, tempID);
    return customer;
}


int checkBarcodeExist(const Product** products, int productsAmount, const char* tempBarcode, const Product** product) {
    for (int i = 0; i < productsAmount; ++i) {
        if (strcmp(products[i]->barcode, tempBarcode) == 0) {
            *product = products[i];
            return 1;
        }
    }
    return 0;
}


Product* getProductToAdd(const Product** products, int productsAmount) {
    char tempBarcode[MAX_LENGTH];
    do {
        printf("Enter an existing product barcode:\n");
        printProductBarcodeRules();
        myGets(tempBarcode, MAX_LENGTH);
    } while (!verifyBarcodeStructure(tempBarcode));

    Product* productToAdd = NULL;
    if (!checkBarcodeExist(products, productsAmount, tempBarcode, &productToAdd))
        printf("No such product barcode\n");

    return productToAdd;
}

int addItemToCart(Customer* customer, const Product** products, int productsAmount) {
    int amountToAdd;
    Product* productToAdd = getProductToAdd(products, productsAmount);
    if (!productToAdd) {
        printf("No such product\n");
        return -1;
    }
    amountToAdd = decreaseAmount(productToAdd);
    if (amountToAdd == -1)
        return -1; //if out of stock
    if (customer->shoppingCart == NULL) {
        ShoppingCart* newCart = malloc(sizeof(ShoppingCart));
        if (!newCart)
            return 0;
        initShoppingCart(newCart);
        customer->shoppingCart = newCart;
    }
    return addItem(customer->shoppingCart, productToAdd->barcode, productToAdd->price, amountToAdd);

}

int shoppingProcess(SuperMarket* superMarket) { //option 3
    int shoppingProcess = 1, res;
    char ch;
    if (!verifyShoppingProcessAllowed(superMarket)) return 2;
    Customer* customer = whoIsShopping(superMarket, 1);
    if (!customer) {
        printf("This customer is not listed\n");
        printf("Error in shopping process\n");
        return 2; //back to menu
    }
    while (shoppingProcess == 1) {
        showProducts(superMarket);
        printf("Do you want to shop for a product? y/Y, anything else to exit!! ");
        do {
            scanf("%c", &ch);
        } while (isspace(ch));
        if (ch == 'y' || ch == 'Y') {
            res = addItemToCart(customer, superMarket->products, superMarket->productsAmount);
            if (res == -1)
                continue;
            if (res == 0) return 0;
        }
        else shoppingProcess = 2;
    }
    printf("---------- Shopping ended ----------\n");
    return shoppingProcess;
}



int verifyShoppingProcessAllowed(const SuperMarket* superMarket) {
    if (!superMarket->customersAmount) {
        printf("No customers listed to markert\n");
        printf("Error in shopping process\n");
        return 0;
    }
    if (!superMarket->productsAmount) {
        printf("No products in market - cannot shop\n");
        printf("Error in shopping process\n");
        return 0;
    }
    return 1;
}



int verifyListedCustomer(const Customer* customers, int customersAmount, const char* tempID) {
    for (int i = 0; i < customersAmount; i++) {
        if (strcmp(customers[i].id, tempID) == 0)
            return 1;
    }
    return 0;
}


void showCustomerCart(const SuperMarket* superMarket) { // option 4
    if (!verifyShoppingProcessAllowed(superMarket)) return;
    Customer* customer = whoIsShopping(superMarket, 1);
    if (!customer) {
        printf("The customer not listed\n");
        return;
    }
    showCart(customer->shoppingCart);
}

void customerCartManagment(SuperMarket* superMarket, Customer* customer) {
    char ch;
    printf("Do you want to pay for the cart? y/Y, anything else to cancel shopping!\n");
    do {
        scanf("%c", &ch);
    } while (isspace(ch));
    if (ch == 'y' || ch == 'Y')
        CartPayment(customer);
    else
        restoreCart(superMarket, customer->shoppingCart);

    freeCart(customer->shoppingCart);
    customer->shoppingCart = NULL;
}

void shoppingCartManagement(SuperMarket* superMarket) { // option 5
    if (!verifyShoppingProcessAllowed(superMarket)) return;
    Customer* customer = whoIsShopping(superMarket, 0);
    if (!customer) {
        printf("this customer not listed\n");
        return;
    }
    if (customer->shoppingCart == NULL) {
        printf("Shopping cart is empty!\n");
        return;
    }
    customerCartManagment(superMarket, customer);
}

void CartPayment(const Customer* customer) {
    printf("---------- Cart info and bill for %s ----------\n", customer->name);
    showCart(customer->shoppingCart);
    printf("--- !!!Payment was recived!!!! --- \n");
}


void restoreCart(SuperMarket* superMarket, ShoppingCart* shoppingCart) {
    int amountOfitemsToRestore = 0;
    for (int i = 0; i < shoppingCart->amount; ++i) {
        char* barcode = shoppingCart->Items[i]->barcode;
        amountOfitemsToRestore = shoppingCart->Items[i]->amount;
        for (int j = 0; j < superMarket->productsAmount; ++j) {
            if (strcmp(barcode, superMarket->products[j]->barcode) == 0) {
                superMarket->products[j]->amount += amountOfitemsToRestore;
                break;
            }
        }
    }
    printf("--- !!!Cart was restored successfully!!!! --- \n");
}

void showProductByType(const SuperMarket* superMarket) { // option 6
    if (superMarket->productsAmount == 0) {
        printf("No products in the market\n");
        return;
    }
    int fType = 0;
    int nType = getType();
    for (int i = 0; i < superMarket->productsAmount; i++)
        if (superMarket->products[i]->type == nType) {
            showProduct(superMarket->products[i]);
            fType = 1;
        }
    if (!fType) {
        printf("There are no products of type %s in the market %s", getTypeName(nType), superMarket->marketName);
    }
}

void exitProgram(SuperMarket* supermarket) { // option -1
    verifyNoOpenCarts(supermarket);
    printf("Exiting program. Freeing resources...\n");
    freeSuperMarket(supermarket);
}

void verifyNoOpenCarts(SuperMarket* superMarket) {
    for (int i = 0; i < superMarket->customersAmount; ++i) {
        if (superMarket->customers[i].shoppingCart != NULL) {
            Customer* customer = &superMarket->customers[i];
            showCustomer(customer);
            showCart(customer->shoppingCart);
            customerCartManagment(superMarket, customer);
        }
    }
    printf("No open carts left :)\n");
}


void freeSuperMarket(SuperMarket* superMarket) {
    free(superMarket->marketName);
    freeProducts(superMarket->products, superMarket->productsAmount);
    freeCustomers(superMarket->customers, superMarket->customersAmount);
}

void freeProducts(Product** products, int productsAmount) {
    for (int i = 0; i < productsAmount; ++i)
        free(products[i]);
    free(products);
}

void freeCustomers(Customer* customers, int customersAmount) {
    for (int i = 0; i < customersAmount; ++i)
        freeCustomer(&customers[i]);
    free(customers);
}


