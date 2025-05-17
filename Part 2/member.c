#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "member.h"

int initMember(Customer* pCustomer) {
    if(!initCustomer(pCustomer))
        return 0;

    Member* member = (Member*)malloc(sizeof(Member));
    if(!member) {
        freeCustomer(pCustomer);
        return 0;
    }
    pCustomer->derivedObj = member;
    member->pBase = pCustomer;

    int flag = 0;
    while(!flag) {
        printf("Please enter the total months of membership\n");
        scanf("%d", &member->totalMonths);
        if(member->totalMonths <= 0) printf("Total months should be positive\n");
        else flag = 1;
    }
    initVTableMember(pCustomer);
    return 1;
}

void initVTableMember(Customer* pCustomer) {
    pCustomer->table.print = printMember;
    pCustomer->table.price = printTotalPriceMember;
    pCustomer->table.free = freeMember;
    pCustomer->table.write = writeMember;
}

void printMember(const Customer* pCustomer) {
    printCustomer(pCustomer);
    Member* pMember = (Member*)pCustomer->derivedObj;
    printf("Total months of membership: %d\n", pMember->totalMonths);
}

void printTotalPriceMember(const Customer* pCustomer, float price) {
    Member* pMember = (Member*)pCustomer->derivedObj;
    float discount;
    if (pMember->totalMonths < TWOYEARS)
        discount = (float)MONTH_DIS * pMember->totalMonths;
    else if(pMember->totalMonths < FIVEYEARS)
        discount = (float)FIVEYEARS_DIS + (float)YEAR_DIS * (pMember->totalMonths / YEAR);
    else
        discount = OVER_FIVEYEARS_DIS;
    printf("Total price for %s is %.2f, after discount of %.2f%%\n",
        pCustomer->name, price * (1 - discount / 100), discount);
}

void freeMember(Customer* pCustomer) {
    if(pCustomer->derivedObj) {
        free(pCustomer->derivedObj);
    }
    freeCustomer(pCustomer);
}

void writeMember(FILE* fp, const Customer* pCust) {
    if(pCust->derivedObj == NULL)
        return;
    Member* pMember = (Member*)pCust->derivedObj;
    fprintf(fp,"%s\n%s\n1 %d\n", pCust->name, pCust->id, pMember->totalMonths);
}

int readMember(FILE* fp, Customer* pCust) {
    Member* member = (Member*)malloc(sizeof(Member));
    if(!member) {
        freeCustomer(pCust);
        return 0;
    }
    pCust->derivedObj = member;
    member->pBase = pCust;
    initVTableMember(pCust);
    if (fscanf(fp, "%d\n", &member->totalMonths)!= 1) {
        freeMember(pCust);
        return 0;
    }
    return 1;
}