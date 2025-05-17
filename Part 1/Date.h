#define _CRT_SECURE_NO_WARNINGS
#ifndef __DATE___
#define __DATE___

#define DATE_LEN 8

typedef struct
{
    int day;
    int month;
    int year;
} Date;

void initDate(Date* date);
int validDate(Date* date, const char* dateStr);
int checkDateString(const char* dateStr);
int convertSplitDate(Date* date, const char* dateStr);
int checkDate(int dd, int mm, int yyyy);
void showDate(const Date* date);
#endif
