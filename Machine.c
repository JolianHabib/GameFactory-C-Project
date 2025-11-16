#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "General.h"
#include "Machine.h"
#include "fileHelper.h"


void initMachine(Machine* pMachine, const Machine** MachineArr,const int numOfMachines)
{
	getSerialNumer(pMachine, MachineArr, numOfMachines);
	getMaterial(&pMachine->Material); 
	getAmountOfMaterial(pMachine);
}

int checkSerialNumberinClass(const int serialNumber,const Machine** MachineArr, const int numOfMachines)
{
	int i;
	for (i = 0;i < numOfMachines;i++)
	{
		if (MachineArr[i]->SerialNumber == serialNumber)
			return 0;
	}
	return 1;

}

void getSerialNumer(Machine* pMachine, const Machine** MachineArr,const int numOfMachines)
{
	int serialnumber, ok=0; 
	do {
		printf("Enter a serial number of machine: (betwen numbers %d - %d) ",MIN_SN, MAX_SN);
		scanf("%d", &serialnumber);
		if (serialnumber >= MIN_SN && serialnumber <= MAX_SN)
		{
			if (checkSerialNumberinClass(serialnumber, MachineArr, numOfMachines) == 1)
			{
				pMachine->SerialNumber = serialnumber;
				ok = 1;
			}
		}
	} while (ok != 1);
}

void getAmountOfMaterial(Machine* pMachine)
{
	int ok = 0;
	double amount;
	do {
		printf("Enter the amonut of material in kg the machine use in a month: ");
		scanf("%lf", &amount);
		if (amount > 1)
		{
			pMachine->amount = amount;
			ok = 1;
		}
	} while (ok != 1);
}

double getMachineExpensesPerMonth(const Machine* pMachine)
{
	return mult(pMachine->Material.price , pMachine->amount);
}

int saveMachineToBinaryFile(const Machine* pMachine, FILE* fp)
{
	
	if (!writeIntToFile(pMachine->SerialNumber, fp, "Error write a Serial Number.\n"))   
		return 0;

	if (saveMaterialToBinaryFileCompressed(&pMachine->Material, fp) == 0)
		return 0;

	if (!writeDoubleToFile(pMachine->amount, fp, "Error write amount of Material the machine used.\n"))    
		return 0; 
	return 1;
	
}

int loadMachineFromBinaryFile(Machine* pMachine, FILE* fp)
{
	memset(pMachine, 0, sizeof(Machine));
	if (!readIntFromFile(&pMachine->SerialNumber, fp, "Error reading Serial Number."))
		return 0;
	if (readMaterialFromBinaryFileCompressed(&pMachine->Material,fp) == 0)
		return 0;
	if (!readDoubleFromFile(&pMachine->amount, fp, "Error reading amount."))
		return 0;
	
	return 1;
}

int saveMachineToFile(const Machine* pMachine, FILE* fp)
{
	if (!pMachine)
		return 0;
	fprintf(fp,"%d\n",pMachine->SerialNumber);
	if (!saveMaterialToFile(&pMachine->Material, fp))
		return 0;
	fprintf(fp, "%lf\n", pMachine->amount);
	return 1;
}

int loadMachineFromFile(Machine* pMachine, FILE* fp)
{
	if (!pMachine)
		return 0;
	fscanf(fp, "%d", &pMachine->SerialNumber); 
	if (!loadMaterialFromFile(&pMachine->Material, fp))
		return 0;
	fscanf(fp, "%lf", &pMachine->amount);
	return 1;

}

void showMachineByMetrial(const Machine* pMachine, const eMaterialType Type)
{
	if (pMachine->Material.type == Type)
		printMachine(pMachine);
}

void printMachine(const Machine* pMachine)
{
	printf("The Machine: Serial Number: %d, it is used %.3lf kg of ", pMachine->SerialNumber, pMachine->amount);
	printMaterial(&pMachine->Material);
}

void freeMachinePtr(void* elment)
{
	Machine* pMachine = *(Machine**)elment;
	free(pMachine);
}

void printMachinePtr(void* elment)
{
	const Machine* pMachine = *(Machine**)elment;
	printMachine(pMachine);
}