#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "Customer.h"

#define YEAR 12
#define TWOYEARS 24
#define FIVEYEARS 60
#define MONTH_DIS 0.1
#define YEAR_DIS 0.5
#define FIVEYEARS_DIS 2.5
#define OVER_FIVEYEARS_DIS 7.5



typedef struct {
    void* pBase;
    int totalMonths;
    VTable table;

}Member;

int     initMember(Customer* pCustomer);
void    initVTableMember(Customer* pCustomer);
void    printMember(const Customer* pCustomer);
void    printTotalPriceMember(const Customer* pCustomer, float price);
void    freeMember(Customer* pCustomer);
void    writeMember(FILE* fp, const Customer* pCust);
int     readMember(FILE* fp, Customer* pCust);