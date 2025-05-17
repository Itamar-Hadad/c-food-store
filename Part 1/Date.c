#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include "Date.h"
#include "generalFunctions.h"

void initDate(Date* date)
{
    char dateStr[MAX_LENGTH];
    do
    {
        printf("Enter a date in \"ddmmyyyy\" format:\n");
        scanf("%s", dateStr);
    } while (!validDate(date, dateStr));
}

int validDate(Date* date, const char* dateStr)
{
    int fValid = 1;

    if (!checkDateString(dateStr))
        fValid = 0;
    if (!convertSplitDate(date, dateStr))
        fValid = 0;
    if (!fValid)
        printf("Date is not valid!!!\n");

    return fValid;
}

int checkDateString(const char* dateStr)
{
    // check string length
    if (strlen(dateStr) != DATE_LEN)
        return 0;

    // validate all values are digits:
    for (int i = 0; i <= DATE_LEN; i++)
    {
        if (dateStr[i] < '0' && dateStr[i] > '9')
            return 0;
    }

    return 1;
}

int convertSplitDate(Date* date, const char* dateStr)
{
    // convert to number
    int dateInt = 0, start_with_zero = 0;

    if (dateStr[0] == '0')
    {
        start_with_zero = 1;
    }

    // Convert dateStr (string) into an integer
    for (int i = 0; i < DATE_LEN; i++) {
        dateInt = dateInt * 10 + (dateStr[i] - '0');
    }
    int dd, mm, yyyy;

    // split into dd, mm, yyyy
    if (start_with_zero == 1)
        dd = dateInt / 100000;
    else dd = dateInt / 1000000;

    mm = (dateInt / 10000) % 100;
    yyyy = dateInt % 10000;

    if (!checkDate(dd, mm, yyyy))
        return 0;

    date->day = dd;
    date->month = mm;
    date->year = yyyy;

    return 1;
}

int checkDate(int dd, int mm, int yyyy) {
    if (yyyy < 2024 || yyyy > 2030)
        return 0;

    if (mm < 1 || mm > 12)
        return 0;

    if (dd < 1 || dd > 31)
        return 0;

    if (dd == 31 && (mm == 4 || mm == 6 || mm == 9 || mm == 11))
        return 0;

    return 1;
}


void showDate(const Date* date)
{
    printf("%02d/%02d/%d\n", date->day, date->month, date->year);
}
