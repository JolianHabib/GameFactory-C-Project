#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#include "Factory.h"
#include "General.h"
#include "fileHelper.h"
#include "FactoryFile.h"


int	initFactoryFromBinaryFile(Factory* pFactory, const char* fileName)
{
	FILE* fp;
	fp = fopen(fileName, "rb");
	if (!fp)
	{
		printf("Error open Factory binary file\n");
		return 0;
	}

	pFactory->WorkerArr = NULL;
	pFactory->DepartmentArr = NULL;
	pFactory->GamesArr = NULL;
	pFactory->CustomerArr = NULL;

	pFactory->FactoryName = readStringFromFile(fp, "Error reading Factory name\n");
	if (!pFactory->FactoryName)
	{
		fclose(fp);
		return 0;
	}

	pFactory->SortBy = eNone;

	if (!readIntFromFile(&pFactory->numOfDepartment, fp, "Error reading Department count\n"))
	{
		free(pFactory->FactoryName);
		fclose(fp);
		return 0;
	}

	if (!createDepartmentArr(pFactory))
	{
		printf("Alocation error\n");
		free(pFactory->FactoryName);
		fclose(fp);
		return 0;
	}

	if (!loadDepartmentArrFromFile(pFactory, fp))
	{
		printf("Error reading departments.\n");
		free(pFactory->FactoryName);
		free(pFactory->DepartmentArr);
		fclose(fp);
		return 0;
	}

	if (!readIntFromFile(&pFactory->numOfWorker, fp, "Error reading Worker count\n"))
	{
		free(pFactory->FactoryName);
		freeDepartmentArr(pFactory);
		fclose(fp);
		return 0;
	}

	if (!createWorkerArr(pFactory))
	{
		printf("Alocation error\n");
		free(pFactory->FactoryName);
		freeDepartmentArr(pFactory); 
		fclose(fp);
		return 0;
	}

	if (!loadWorkerArrFromFile(pFactory, fp))
	{
		printf("Error reading Workers\n");
		free(pFactory->FactoryName);
		freeDepartmentArr(pFactory);
		free(pFactory->WorkerArr);
		fclose(fp);
		return 0;
	}

	if (!readIntFromFile(&pFactory->numOfGames, fp, "Error reading game count.\n"))
	{
		free(pFactory->FactoryName);
		freeDepartmentArr(pFactory); 
		freeWorkerArr(pFactory); 
		fclose(fp);
		return 0;	
	}
	
	pFactory->GamesArr = (Game*)calloc(pFactory->numOfGames, sizeof(Game)); 

	if (!loadGameArrFromFile(pFactory, fp)) 
	{
		printf("Error reading Games.\n");
		free(pFactory->FactoryName);
		freeDepartmentArr(pFactory);
		freeWorkerArr(pFactory);  
		free(pFactory->GamesArr);
		fclose(fp);
		return 0;
	}

	if (!readIntFromFile(&pFactory->numOfCustomers, fp, "Error reading Customer count \n"))
	{
		free(pFactory->FactoryName);
		freeDepartmentArr(pFactory);
		freeWorkerArr(pFactory);
		freeGameArr(pFactory);
		fclose(fp);
		return 0;
	}
	pFactory->CustomerArr = (Customer*)calloc(pFactory->numOfCustomers, sizeof(Customer));

	if (!loadCustomerArrFromFile(pFactory, fp))
	{
		printf("Error reading Customers.\n");
		free(pFactory->FactoryName);
		freeDepartmentArr(pFactory);
		freeWorkerArr(pFactory);
		freeGameArr(pFactory);
		free(pFactory->CustomerArr);
		fclose(fp);
		return 0;
	}
	fclose(fp);
	return 1;
}

int createWorkerArr(Factory* pFactory)
{
	if (pFactory->numOfWorker > 0)
	{
		pFactory->WorkerArr = (Worker**)malloc(pFactory->numOfWorker * sizeof(Worker*));
		if (!pFactory->WorkerArr)
		{
			printf("Alocation error\n");
			return 0;
		}
	}
	else
		pFactory->WorkerArr = NULL; 

	for (int i = 0; i < pFactory->numOfWorker; i++)
	{
		pFactory->WorkerArr[i] = (Worker*)calloc(1, sizeof(Worker));
		if (!pFactory->WorkerArr[i])
		{
			printf("Alocation error\n");
			return 0;
		}
	}
	return 1;
}

int loadWorkerArrFromFile(Factory* pFactory, FILE* fp)
{
	for (int i = 0; i < pFactory->numOfWorker; i++)
	{
		if (!loadWorkerFromBinaryFile(pFactory->WorkerArr[i], fp))
		{
			return 0;
			
		}
		pFactory->WorkerArr[i]->Department = findDepartmentByCode(pFactory->WorkerArr[i]->code, pFactory->DepartmentArr, pFactory->numOfDepartment);
	}
	return 1;
}

int createDepartmentArr(Factory* pFactory)
{
	if (pFactory->numOfDepartment > 0)
	{
		pFactory->DepartmentArr = (Department**)malloc(pFactory->numOfDepartment * sizeof(Department*));
		if (!pFactory->DepartmentArr)
		{
			printf("Alocation error\n");
			return 0;
		}
	}
	else
		pFactory->DepartmentArr = NULL;

	for (int i = 0; i < pFactory->numOfDepartment; i++)
	{
		pFactory->DepartmentArr[i] = (Department*)calloc(1, sizeof(Department));
		if (!pFactory->DepartmentArr[i])
		{
			printf("Alocation error\n");
			return 0;
		}
	}
	return 1;
}

int loadDepartmentArrFromFile(Factory* pFactory, FILE* fp)
{
	for (int i = 0; i < pFactory->numOfDepartment; i++)
	{
		if (!loadDepartmentFromBinaryFile(pFactory->DepartmentArr[i], fp))
		{
			return 0;
		}
	}
	return 1;
}

int loadCustomerArrFromFile(Factory* pFactory, FILE* fp) 
{

	for (int i = 0; i < pFactory->numOfCustomers; i++)
	{
		if (!loadCustomerFromBinaryFile(&pFactory->CustomerArr[i], fp))  
		{
			return 0;
		}
	}
	return 1;
}

int loadGameArrFromFile(Factory* pFactory, FILE* fp)
{
	for (int i = 0; i < pFactory->numOfGames; i++)
	{
		if (!loadGameFromBinaryFile(&pFactory->GamesArr[i], fp))
		{
			return 0;
		}
	}
	return 1;
}

int		saveFactoryToBinaryFile(const Factory* pFactory, const char* fileName)
{
	FILE* fp;
	fp = fopen(fileName, "wb");
	if (!fp) {
		printf("Error open Factory binary file to write\n");
		return 0;
	}

	if (!writeStringToFile(pFactory->FactoryName, fp, "Error write Factory name\n"))
	{
		fclose(fp);
		return 0;
	}
	
	if (!writeIntToFile(pFactory->numOfDepartment, fp, "Error write Department count\n"))
	{
		fclose(fp);
		return 0;
	}

	for (int i = 0; i < pFactory->numOfDepartment; i++)
	{
		if (!saveDepartmentToBinaryFile(pFactory->DepartmentArr[i], fp))
		{
			fclose(fp);
			return 0;
		}
	}

	if (!writeIntToFile(pFactory->numOfWorker, fp, "Error write Worker count\n"))
	{
		fclose(fp);
		return 0;
	}

	for (int i = 0; i < pFactory->numOfWorker; i++)
	{
		if (!saveWorkerToBinaryFile(pFactory->WorkerArr[i], fp))
		{
			fclose(fp);
			return 0;
		}
	}

	if (!writeIntToFile(pFactory->numOfGames, fp, "Error write game count\n"))
	{
		fclose(fp);
		return 0;
	}

	for (int i = 0; i < pFactory->numOfGames; i++)
	{
		if (!saveGameToBinaryFile(&pFactory->GamesArr[i], fp)) 
		{
			fclose(fp);
			return 0;
		}
	}
	
	if (!writeIntToFile(pFactory->numOfCustomers, fp, "Error write Customer count\n"))
	{
		fclose(fp);
		return 0;
	}

	for (int i = 0; i < pFactory->numOfCustomers; i++)
	{
		if (!saveCustomerToBinaryFile(&pFactory->CustomerArr[i], fp))
		{
			fclose(fp);
			return 0;
		}
	}

	fclose(fp);
	return 1;
}


int initFactoryFromFile(Factory* pFactory, const char* fileName)
{

	FILE* fp;
	fp = fopen(fileName, "r");
	if (!fp)
	{
		printf("Error open Factory Text file\n");
		return 0;
	}

	pFactory->WorkerArr = NULL;
	pFactory->DepartmentArr = NULL;
	pFactory->GamesArr = NULL;
	pFactory->CustomerArr = NULL;
	pFactory->SortBy = eNone; 
	pFactory->FactoryName = readDynStringFromTextFile(fp);

	if (!pFactory->FactoryName)
	{
		fclose(fp);
		return 0;
	}

	fscanf(fp, "%d", &pFactory->numOfDepartment);

	if (!createDepartmentArr(pFactory)) 
	{
		printf("Alocation error\n");
		free(pFactory->FactoryName);
		fclose(fp);
		return 0;
	}

	if (!loadDepartmentArrFromTextFile(pFactory, fp))
	{
		printf("Error reading Department.\n");
		free(pFactory->FactoryName); 
		free(pFactory->DepartmentArr);
		fclose(fp);
		return 0;
	}

	fscanf(fp, "%d", &pFactory->numOfWorker);
	
	if (!createWorkerArr(pFactory))
	{
		printf("Alocation error\n");
		free(pFactory->FactoryName);
		freeDepartmentArr(pFactory);
		fclose(fp);
		return 0;
	}

	if (!loadWorkerArrFromTextFile(pFactory, fp)) 
	{
		printf("Error reading Workers.\n");
		free(pFactory->FactoryName);
		freeDepartmentArr(pFactory); 
		free(pFactory->WorkerArr);
		fclose(fp);
		return 0;
	}

	fscanf(fp, "%d", &pFactory->numOfGames); 
	
	pFactory->GamesArr = (Game*)calloc(pFactory->numOfGames, sizeof(Game)); 
	if (!pFactory->GamesArr)
	{
		printf("Alocation error\n");
		free(pFactory->FactoryName);
		freeDepartmentArr(pFactory);
		freeWorkerArr(pFactory);
		fclose(fp);
		return 0;
	} 

	if (!loadGameArrFromTextFile(pFactory, fp)) 
	{
		printf("Error reading Games\n");
		free(pFactory->FactoryName);
		free(pFactory->WorkerArr);
		free(pFactory->GamesArr);
		fclose(fp);
		return 0;
	}

	fscanf(fp, "%d", &pFactory->numOfCustomers);
	pFactory->CustomerArr = (Customer*)calloc(pFactory->numOfCustomers, sizeof(Customer));
	if (!pFactory->CustomerArr)
	{
		printf("Alocation error\n");
		free(pFactory->FactoryName);
		freeDepartmentArr(pFactory);
		freeWorkerArr(pFactory);
		freeGameArr(pFactory);
		fclose(fp);
		return 0;
	}

	if (!loadCustomerArrFromTextFile(pFactory, fp))  
	{
		printf("Error reading Customers.\n");
		free(pFactory->FactoryName);
		freeDepartmentArr(pFactory);
		freeWorkerArr(pFactory);
		freeGameArr(pFactory);
		free(pFactory->CustomerArr);
		fclose(fp);
		return 0;
	}

	fclose(fp);
	return 1;
}

int loadDepartmentArrFromTextFile(Factory* pFactory, FILE* fp)
{

	for (int i = 0; i < pFactory->numOfDepartment; i++)
	{
		if (!loadDepartmentFromFile(pFactory->DepartmentArr[i], fp)) 
		{ 
			return 0;
		}
	}
	return 1;
}

int loadWorkerArrFromTextFile(Factory* pFactory, FILE* fp) 
{
	for (int i = 0; i < pFactory->numOfWorker; i++)
	{
		if (!loadWorkerFromFile(pFactory->WorkerArr[i], fp))
			return 0;
		pFactory->WorkerArr[i]->Department = findDepartmentByCode(pFactory->WorkerArr[i]->code, pFactory->DepartmentArr, pFactory->numOfDepartment);
	}
	return 1;
}

int loadGameArrFromTextFile(Factory* pFactory, FILE* fp)
{
	for (int i = 0; i < pFactory->numOfGames; i++)
	{
		if (!loadGameFromFile(&pFactory->GamesArr[i], fp))
		{
			return 0;
		}
	}
	return 1;
}

int loadCustomerArrFromTextFile(Factory* pFactory, FILE* fp)
{
	for (int i = 0; i < pFactory->numOfCustomers; i++)
	{
		if (!loadCustomerFromFile(&pFactory->CustomerArr[i], fp))
			return 0;
	}
	return 1;
}

int saveFactoryToTextFile(const Factory* pFactory, const char* fileName)
{
	FILE* fp;
	fp = fopen(fileName, "w");
	if (!fp) {
		printf("Error open Factory Text file to write\n");
		return 0;
	}

	fprintf(fp, "%s\n", pFactory->FactoryName);
	fprintf(fp, "%d\n", pFactory->numOfDepartment);
	for (int i = 0; i < pFactory->numOfDepartment; i++)
	{
		if (!saveDepartmentToFile(pFactory->DepartmentArr[i], fp) )
		{
			fclose(fp);
			return 0;
		}
	}
	fprintf(fp, "%d\n", pFactory->numOfWorker);
	
	for (int i = 0; i < pFactory->numOfWorker; i++)
	{
		if (!saveWorkerToFile(pFactory->WorkerArr[i], fp))
		{
			fclose(fp);
			return 0;
		}
	}
	fprintf(fp, "%d\n", pFactory->numOfGames);
	
	for (int i = 0; i < pFactory->numOfGames; i++)
	{
		if (!saveGameToFile(&pFactory->GamesArr[i], fp)) 
		{
			fclose(fp);
			return 0;
		}
	}
	fprintf(fp, "%d\n", pFactory->numOfCustomers);

	for (int i = 0; i < pFactory->numOfCustomers; i++)
	{
		if (!saveCustomerToFile(&pFactory->CustomerArr[i], fp))
		{
			fclose(fp);
			return 0;
		}
	}
	fclose(fp);
	return 1;
}
