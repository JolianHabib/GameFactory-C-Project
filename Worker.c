#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "Worker.h"
#include "General.h"
#include "fileHelper.h"



int	isIDNumber(const Worker* pWorker, const char* IDNumber)
{
	if (!pWorker)
		return 0;
	if (strcmp(pWorker->ID, IDNumber) == 0)
		return 1;

	return 0;
}

int checkDepartmentCodeForWorker(Worker* pWorker, char* DepartmentCode)
{
	if(strcmp(pWorker->Department->DepartmentCode, DepartmentCode)==0)
    	return 1;
	return 0;
}

int	initWorkerWithoutDepartment(Worker* pWorker,const  Worker** WorkerArr,const int numOfWorker)
{
	if (getName(pWorker)==0)
		return 0;
	getSalay(pWorker);
	getIDNumber(pWorker,WorkerArr,numOfWorker);
	initAddress(&pWorker->address);
	getCorrectDate(&pWorker->date);
	return 1;
}

int getName(Worker* pWorker)
{
	pWorker->name = getStrExactName("Enter Worker full Name\t");
	if (!pWorker->name)
		return 0;
	return 1;
}
Worker* findWorkerById(Worker** workerArr,const int numOfWorker,const char* ID) 
{
	int i;
	for (i = 0;i < numOfWorker;i++)
	{
		if (isIDNumber(workerArr[i], ID) == 1)
			return workerArr[i];
	}
	return NULL; 
}

void getIDNumber(Worker* pWorker,const Worker** WorkerArr,const int numOfWorker)
{
	char temp[MAX_STR_LEN];
	int ok = 1;
	do {
		ok = 1;
		printf("Enter Id Number of the worker  - %d digits\t", IDLEN);
		myGets(temp, MAX_STR_LEN, stdin);
		if (strlen(temp) != IDLEN)
		{
			printf("Id number should be %d digits\n", IDLEN);
			ok = 0;
		}
	    if (checkDigitId(temp) == 0)
		{
			printf("Need to be digits\n");
			ok = 0;
		}
		 if (checkUniqeId(WorkerArr, numOfWorker,temp)==0)
		 {
			 printf("This ID number in use.\n");
			 ok = 0;
		 }
	} while (!ok);
	strcpy(pWorker->ID, temp);
}

int checkDigitId(const char* temp)
{
	for (int i = 0; i < IDLEN; i++)
	{
		if (isdigit(temp[i]) == 0)
		{
			return 0;
		}
	}
	return 1;
}

int checkUniqeId(Worker** workerArr,const int numOfWorker,const char* ID)
{ 
	Worker* pWorker = findWorkerById(workerArr, numOfWorker, ID);
	if (pWorker == NULL)
		return 1;
	return 0;
}

void getSalay(Worker* pWorker)
{
	double salary;
	int ok = 0;
	do {
		printf("Enter the worker salary In Shekel: ");
		scanf("%lf", &salary);
		if (salary > 0)
		{
			pWorker->salary = salary;
			ok = 1;
		}

	} while (ok != 1);
}

int compareByName(const void* worker1, const void* worker2)
{
	const Worker* pworker1 = *(const Worker**)worker1;
	const Worker* pworker2 = *(const Worker**)worker2;
	return strcmp(pworker1->name, pworker2->name);
}

int compareBySalary(const void* worker1, const void* worker2)
{
	const Worker* pworker1 = *(const Worker**)worker1;
	const Worker* pworker2 = *(const Worker**)worker2;
	double num;
	num = sub(pworker1->salary , pworker2->salary); 
	if (num > 0.0)
		return 1;
	else if (num < 0.0)
		return -1;
	else
		return 0;
	
}

int compareByDate(const void* worker1, const void* worker2)
{
	const Worker* pworker1 = *(const Worker**)worker1;
	const Worker* pworker2 = *(const Worker**)worker2;
	if (pworker1->date.year > pworker2->date.year) 
		return 1;
	if (pworker1->date.year < pworker2->date.year) 
		return -1;

	if (pworker1->date.month > pworker2->date.month)
		return 1;
	if (pworker1->date.month < pworker2->date.month)
		return -1;

	if (pworker1->date.day > pworker2->date.day)
		return 1;
	if (pworker1->date.day < pworker2->date.day) 
		return -1;

	return 0; //if have same date
}

int saveWorkerToBinaryFile(const Worker* pWorker, FILE* fp)
{
	if (!writeStringToFile(pWorker->name, fp, "Error write Worker name.\n"))
		return 0;
	if (!writeCharsToFile(pWorker->ID,IDLEN,fp,"Error write Worker Id.\n"))
		return 0;
	if (!writeDoubleToFile(pWorker->salary, fp, "Error write Worker salary.\n"))
		return 0;
	if (!saveAddressToBinaryFile(&pWorker->address, fp))
		return 0;
	if (!saveDateToBinaryFile(&pWorker->date, fp))
		return 0;
	if (!writeCharsToFile(pWorker->Department->DepartmentCode, CODELEN, fp, "Error write department code.\n"))
		return 0;
	
	return 1;
}

int loadWorkerFromBinaryFile(Worker* pWorker,FILE* fp)
{
	
	memset(pWorker, 0, sizeof(Worker));
	pWorker->name = readStringFromFile(fp, "Error reading Worker name.\n");
	if (!pWorker->name)
		return 0;
	if (!readCharsFromFile(pWorker->ID, IDLEN, fp, "Error reading Worker Id.\n"))
		return 0;
	if (!readDoubleFromFile(&pWorker->salary, fp, "Error reading Worker salary.\n"))
		return 0;
	if (!loadAddressFromBinaryFile(&pWorker->address, fp))
		return 0;
	if (!loadDateFromBinaryFile(&pWorker->date, fp)) 
		return 0;
	if (!readCharsFromFile(pWorker->code, CODELEN, fp, "Error read department code"))
		return 0; 
	pWorker->Department = NULL;
	
	return 1;
}

int saveWorkerToFile(const Worker*pWorker, FILE* fp)
{
	fprintf(fp,"%s\n", pWorker->name);
	fprintf(fp,"%s\n", pWorker->ID);
	fprintf(fp,"%lf\n", pWorker->salary);
	if (!saveAddressToFile(&pWorker->address, fp))
		return 0;
	if (!saveDateToFile(&pWorker->date, fp))
		return 0;
	fprintf(fp, "%s\n", pWorker->Department->DepartmentCode);

	return 1;
}

int loadWorkerFromFile(Worker* pWorker,FILE* fp)
{
	pWorker->name = readDynStringFromTextFile(fp);
	fscanf(fp, "%s", pWorker->ID);
	fscanf(fp, "%lf", &pWorker->salary);
	if (!loadAddressFromFile(&pWorker->address, fp))
		return 0;
	if(!loadDateFromFile(&pWorker->date, fp))
		return 0;
	fscanf(fp,"%s",pWorker->code); 
	return 1;

}

void freeWorker(void* elment)
{
	Worker* pWorker = *(Worker**)elment; 
	free(pWorker->name); 
	free(pWorker);

}

void printWorker(const Worker* pWorker)
{
	
    printf("The Worker %s, his/her Id number %s,works in %s Department, Department's code is %s, his/her monthly salary %.3lf Shekel, work start ",pWorker->name, pWorker->ID,pWorker->Department->DepartmentName,pWorker->Department->DepartmentCode ,pWorker->salary);
	printDate(&pWorker->date);
	printAddress(&pWorker->address);
	printf("\n");
}

void printWorkerPtr(void* elment)
{
	const Worker* pWorker = *(Worker**)elment; 
	printWorker(pWorker);
}