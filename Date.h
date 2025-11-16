#pragma once

#define MAX_YEAR 2024 

typedef struct
{
	int			day;
	int			month;
	int			year;
}Date;

void getCorrectDate(Date* pDate);
int	checkDate(char* date, Date* pDate);
int	saveDateToBinaryFile(const Date* pDate, FILE* fp);
int	loadDateFromBinaryFile(Date* pDate, FILE* fp);
int	loadDateFromFile(Date* pDate, FILE* fp);
int	saveDateToFile(const Date* pDate, FILE* fp);
void printDate(const Date* pDate);

