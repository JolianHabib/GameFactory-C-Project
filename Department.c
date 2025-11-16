#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Department.h" 
#include "General.h"
#include "fileHelper.h"


int initDepartment(Department* pDepartment, const Department** DepartmentArr,  const int numOfDepartment)
{
	pDepartment->DepartmentName = getStrExactName("Enter Department Name");
	if (!pDepartment->DepartmentName)
		return 0;
	getDepartmentCode(pDepartment, DepartmentArr,numOfDepartment);
	pDepartment->MachineArr = NULL;
	pDepartment->numOfMachines = 0;
	return 1;
}

int AddMachine(Department* pDepartment)
{
	Machine* pMachine = (Machine*)calloc(1, sizeof(Machine));
	if (!pMachine)
		return 0;
	initMachine(pMachine, pDepartment->MachineArr, pDepartment->numOfMachines);
	pDepartment->MachineArr = (Machine**)realloc(pDepartment->MachineArr, ((pDepartment->numOfMachines )+ 1) * sizeof(Machine*));
	if (!pDepartment->MachineArr)
	{
		free(pMachine);
		return 0;
	}
	pDepartment->MachineArr[pDepartment->numOfMachines] = pMachine;
	pDepartment->numOfMachines++;
	return 1; 

}

void getDepartmentCode(Department* pDepartment,const Department** DepartmentArr,const int numOfDepartment)
{
	int ok=0;
	char codeTemp[MAX_STR_LEN];
	do {
		printf("Enter Department Code: (must be one Charchter in the first and one digit) ");
		scanf("%s", codeTemp);
		if (checkCode(codeTemp) == 1)
		{
			if (islower(codeTemp[0]) != 0)
				codeTemp[0] = toupper(codeTemp[0]);
			if (checkUniqeCode(codeTemp, DepartmentArr, numOfDepartment) == 1) 
				ok = 1;
		}
		
	} while (ok != 1);
	strcpy(pDepartment->DepartmentCode, codeTemp); 
}

int checkUniqeCode(char* code, Department** DepartmentArr,const int numOfDepartment)
{
	Department* pDepartment = findDepartmentByCode(code, DepartmentArr, numOfDepartment);
	if (pDepartment != NULL) 
		return 0;

	return 1;
}

Department* findDepartmentByCode(char* code, Department** DepartmentArr,const int numOfDepartment)
{
	int i ;
	Department temp = { 0 };
	strcpy(temp.DepartmentCode, code);
	for (i = 0;i < numOfDepartment;i++)
	{
		if (strcmp(temp.DepartmentCode, DepartmentArr[i]->DepartmentCode) == 0)
			return DepartmentArr[i];
	}
	return NULL;
}
double getDepartmentExpensesPerMonth(const Department* pDepartment)
{
	int i;
	double sum=0;
	for (i = 0;i < pDepartment->numOfMachines;i++)
	{
		sum = (sum + getMachineExpensesPerMonth(pDepartment->MachineArr[i]));
	}
	return sum;
}

int checkCode(const char* code)
{
	if (strlen(code) != CODELEN)
		return 0;
	if((code[0]<'A' || code[0]>'Z') && (code[0] < 'a' || code[0]>'z'))
		return 0;
	if (isdigit(code[1]) == 0)
		return 0;
	return 1;
}

void  showMachinesByMaterialInDepartment(const Department* pDepartment,const eMaterialType Type) 
{
	int i;
	for (i = 0;i < pDepartment->numOfMachines;i++)
		showMachineByMetrial(pDepartment->MachineArr[i],Type); 

}

int saveDepartmentToBinaryFile(const Department* pDepartment, FILE* fp)
{

	if (!writeStringToFile(pDepartment->DepartmentName, fp, "Error write Department Name.\n"))
		return 0;
	if (!writeCharsToFile(pDepartment->DepartmentCode, CODELEN, fp, "Error write Department code.\n"))
		return 0;
	if (!writeIntToFile(pDepartment->numOfMachines, fp, "Error write number of machines in the Department.\n"))
		return 0;
	for (int i = 0; i < pDepartment->numOfMachines; i++)
	{
		if (!saveMachineToBinaryFile(pDepartment->MachineArr[i],fp))
			return 0;	
	}

	return 1;
}

int loadDepartmentFromBinaryFile(Department* pDepartment, FILE* fp)
{
	memset(pDepartment, 0, sizeof(Department));
	pDepartment->DepartmentName = readStringFromFile(fp, "Error reading Department name.\n");
	if (!pDepartment->DepartmentName)
		return 0;
	if (!readCharsFromFile(pDepartment->DepartmentCode, CODELEN, fp, "Error reading Department code.\n"))
		return 0;
	if (!readIntFromFile(&pDepartment->numOfMachines, fp, "Error reading number of Machines in the Department.\n"))
		return 0;
	if (!createMachineArr(pDepartment))
		return 0;
	for (int i = 0; i < pDepartment->numOfMachines; i++)
	{
		if (!loadMachineFromBinaryFile(pDepartment->MachineArr[i], fp))
		{
			return 0;
		}
	}

	return 1;
}

int saveDepartmentToFile(const Department* pDepartment, FILE* fp)
{
	if (!pDepartment)
		return 0;
	fprintf(fp, "%s\n", pDepartment->DepartmentName);
	fprintf(fp, "%s\n", pDepartment->DepartmentCode);
	fprintf(fp, "%d\n", pDepartment->numOfMachines);
	for (int i = 0;i < pDepartment->numOfMachines;i++)
	{
		if (!saveMachineToFile(pDepartment->MachineArr[i], fp))
			return 0;
	}
	return 1;
}

int loadDepartmentFromFile(Department* pDepartment,FILE* fp)
{
	if (!pDepartment)
		return 0;
	pDepartment->DepartmentName = readDynStringFromTextFile(fp);
	fscanf(fp, "%s", pDepartment->DepartmentCode);
	fscanf(fp, "%d", &pDepartment->numOfMachines);
	if (!createMachineArr(pDepartment))
		return 0;
	for (int i = 0; i < pDepartment->numOfMachines; i++)
	{
		if (!loadMachineFromFile(pDepartment->MachineArr[i], fp))
		{
			return 0;
		}
	}
	return 1;
}

int createMachineArr(Department* pDepartment)
{
	if (pDepartment->numOfMachines > 0)
	{
		pDepartment->MachineArr = (Machine**)malloc(pDepartment->numOfMachines * sizeof(Machine*));
		if (!pDepartment->MachineArr)
		{
			printf("Alocation error\n");
			return 0;
		}
	}
	else
		pDepartment->MachineArr = NULL;

	for (int i = 0; i < pDepartment->numOfMachines; i++)
	{
		pDepartment->MachineArr[i] = (Machine*)calloc(1, sizeof(Machine));
		if (!pDepartment->MachineArr[i])
		{
			printf("Alocation error\n");
			return 0;
		}
	}
	return 1;
}

void printDepartment(const Department* pDepartment)
{
	printf("The Department name: %s ,By code is: %s has %d Machines\n", pDepartment->DepartmentName, pDepartment->DepartmentCode, pDepartment->numOfMachines);
	printMachinesArray(pDepartment);
}

void printDepartmentPtr(void* elment)
{
	const Department* pDepartment = *(Department**)elment;
	printDepartment(pDepartment);
	printf("\n");
}

void printDepartmentwithouMachine(const Department* pDepartment)
{
	printf("The Department name: %s ,By code is: %s has %d Machines\n", pDepartment->DepartmentName, pDepartment->DepartmentCode, pDepartment->numOfMachines);
}

void printMachinesArray(const Department* pDepartment) 
{
	generalArrayFunction(pDepartment->MachineArr, pDepartment->numOfMachines, sizeof(Machine*), printMachinePtr); 
}

void freeDepartment(void* elment)
{
	Department* pDepartment = *(Department**)elment;
	free(pDepartment->DepartmentName);
	freeMachinestArr(pDepartment->MachineArr, pDepartment->numOfMachines); 
	free(pDepartment); 
}

void freeMachinestArr(Machine** arr, int size) 
{
	generalArrayFunction(arr, size, sizeof(Machine*), freeMachinePtr);  	
}


