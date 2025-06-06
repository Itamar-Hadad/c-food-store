#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "Date.h"
#include "General.h"
#include "FileHelper.h"

int initDate(Date* pDate)
{
	char dateStr[MAX_STR_LEN];
	char msg[MAX_STR_LEN];
	int ok = 1;
	printf("\n");
	sprintf(msg, "Enter a date in \"ddmmyyyy\" format:");
	do
	{
		getsStrFixSize(dateStr, sizeof(dateStr), msg);
		if (strlen(dateStr) != DATE_FORMAT_LEN)
		{
			printf("Date should be 8 characters!\n");
			ok = 0;
		}
		else
		{
			ok = sscanf(dateStr, "%2d%2d%4d", &pDate->day, &pDate->month, &pDate->year) == 3;
			if (!ok)
				printf("Date format is not valid!!!\n");
			if (ok && !isValidDate(pDate->day, pDate->month, pDate->year))
			{
				printf("Date is not valid!!!\n");
				ok = 0;
			}
		}
	} while (!ok);
	return ok;
}

int isValidDate(int day, int month, int year)
{
	if (year < MIN_YEAR || year > MAX_YEAR || month < 1 || month > 12 || day < 1)
		return 0;

	int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

	if (day > daysInMonth[month - 1])
		return 0;

	return 1;
}

void printDate(const Date* pDate)
{
	printf("%02d/%02d/%04d\n", pDate->day, pDate->month, pDate->year);
}

char* getDateStr(const Date* pDate)
{
	char* str = (char*)malloc(MAX_DATE_STR_LEN * sizeof(char));
	if (!str)
		return NULL;
	sprintf(str, "%02d/%02d/%04d", pDate->day, pDate->month, pDate->year);
	return str;
}

int saveDateToFile(const Date* pDate, FILE* fp)
{
	if (!writeStringToFile(getDateStr(pDate), fp, "Error writing date\n"))
		return 0;
	return 1;
}

int loadDateFromFile(Date* pDate, FILE* fp)
{
	char dateStr[MAX_DATE_STR_LEN];
	if (!readFixSizeStrFromFile(dateStr, fp, "Error reading date\n"))
		return 0;
	return sscanf(dateStr, "%2d/%2d/%4d", &pDate->day, &pDate->month, &pDate->year) == 3;
}
int saveDateToFileComp(const Date* date, FILE* fp) {
	BYTE temp[2];
	temp[0] = date->day << 3;
	temp[0] |= date->month >> 1;
	temp[1] = date->month << 7;
	temp[1] |= (date->year - 2024) << 4 ;
	if(fwrite(temp, sizeof(BYTE), 2, fp) != 2) {
		printf("Error write product expired date\n");
		return 0;
	}
	return 1;
}

int loadDatefromFileComp(Date* date, FILE* fp) {
	BYTE temp[2];
	if(fread(temp, sizeof(BYTE), 2, fp) != 2) {
		printf("Error read date\n");
		return 0;
	}
	date->year = ((temp[1] >> 4) & 0x7) + 2024;
	date->month = ((temp[0] & 0x7) << 1) | ((temp[1] >> 7) & 0x1);
	date->day = (temp[0] >> 3) & 0x1F;
	return 1;
}