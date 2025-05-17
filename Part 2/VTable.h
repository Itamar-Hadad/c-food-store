#define _CRT_SECURE_NO_WARNINGS
#pragma once


struct _Customer;

typedef struct {

    void (*print)(const struct _Customer* pCustomer);
    void (*price)(const struct _Customer* pCustomer, float price);
    void (*free)(struct _Customer* pCustomer);
    void (*write)(FILE* fp,const struct _Customer* pCust);

}VTable;