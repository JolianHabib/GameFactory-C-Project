#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "Date.h" 
#include "General.h"


const int DAY_MONTHS[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
#define SPECIAL_TAV '#'

void getCorrectDate(Date* pDate)   
{
	char date[MAX_STR_LEN];
	int ok = 1;

	do {
		printf("Enter the worker's start date  dd%c%cmm%c%cyyyy  maximum year %d\t",
			SPECIAL_TAV, SPECIAL_TAV, SPECIAL_TAV, SPECIAL_TAV, MAX_YEAR);
		myGets(date, MAX_STR_LEN, stdin);
		ok = checkDate(date, pDate);
		if (!ok)
			printf("Error try again\n");
	} while (!ok);
}


int	 checkDate(char* date, Date* pDate)
{
	int day, month, year;
	if (strlen(date) != 12)
		return 0;
	if ((date[2] != SPECIAL_TAV) || (date[3] != SPECIAL_TAV)
		|| (date[6] != SPECIAL_TAV) || (date[7] != SPECIAL_TAV))
		return 0;
	sscanf(date, "%d%*c%*c%d%*c%*c%d", &day, &month, &year);
	if (day < 1 || month < 1 || month > 12 || year > MAX_YEAR)
		return 0;

	if (day > DAY_MONTHS[month - 1])
		return 0;

	pDate->day = day;
	pDate->month = month;
	pDate->year = year;

	return 1;
}

int	saveDateToBinaryFile(const Date* pDate, FILE* fp)
{
	if (fwrite(pDate, sizeof(Date), 1, fp) != 1)
	{
		printf("Error write date\n");
		return 0;
	}

	return 1;

}

int	loadDateFromBinaryFile(Date* pDate, FILE* fp)
{
	
	if (fread(pDate, sizeof(Date), 1, fp) != 1)
	{
		printf("Error read date\n");
		return 0;
	}

	return 1;

}
int	saveDateToFile(const Date* pDate, FILE* fp)
{
	if (!pDate)
		return 0;
	if (pDate->day < 10)
		fprintf(fp, "%s", "0");
	fprintf(fp, "%d##", pDate->day);
	if (pDate->month < 10)
		fprintf(fp, "%s", "0");
	fprintf(fp, "%d##%d\n", pDate->month,pDate->year);
		
	
	return 1;
}

int	loadDateFromFile(Date* pDate, FILE* fp)
{
	char temp[MAX_STR_LEN];
	if (!pDate)
		return 0;

	myGets(temp, MAX_STR_LEN, fp);
	checkDate(temp,pDate);
	return 1;
}

void printDate(const Date* pDate)
{
	printf("Date: %d/%d/%d\n", pDate->day, pDate->month, pDate->year);
}

