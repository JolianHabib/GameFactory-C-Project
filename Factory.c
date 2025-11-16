#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Factory.h"
#include "General.h"

int initFactory(Factory* pFactory)
{
	pFactory->FactoryName = getStrExactName("Enter Factory Name");
	if (!pFactory->FactoryName)
		return 0;
	pFactory->WorkerArr = NULL;
	pFactory->numOfWorker = 0;
	pFactory->DepartmentArr = NULL;
	pFactory->numOfDepartment = 0;
	pFactory->GamesArr = NULL; 
	pFactory->numOfGames = 0;
	pFactory->CustomerArr = NULL;
	pFactory->numOfCustomers = 0;
	pFactory->SortBy = 0;
	return 1;
}

int AddWorker(Factory* pFactory)
{
	if (pFactory->numOfDepartment > 0)
	{
		Worker* pWorker = (Worker*)calloc(1, sizeof(Worker));
		if (!pWorker)
			return 0;
		initWorkerWithoutDepartment(pWorker, pFactory->WorkerArr, pFactory->numOfWorker);
		AddDepartmentToWorker(pFactory, pWorker);
		pFactory->WorkerArr = (Worker**)realloc(pFactory->WorkerArr,( pFactory->numOfWorker + 1) * sizeof(Worker*));
		if (!pFactory->WorkerArr)
		{
			free(pWorker);
			return 0;
		}
		pFactory->WorkerArr[pFactory->numOfWorker] = pWorker;
		pFactory->numOfWorker++;
		return 1;
	}
	else
	{
		printf("Please Add Department first!. ");
		return 0;
	}
}

int AddDepartment(Factory* pFactory)
{
	Department* pDepartment = (Department*)calloc(1, sizeof(Department));
	if (!pDepartment)
		return 0;
	if (initDepartment(pDepartment, pFactory->DepartmentArr, pFactory->numOfDepartment) == 0)
		return 0;
	pFactory->DepartmentArr = (Department**)realloc(pFactory->DepartmentArr, (pFactory->numOfDepartment + 1) * sizeof(Department*));
	if (!pFactory->DepartmentArr)
	{
		free(pDepartment);
		return 0;
	}
	pFactory->DepartmentArr[pFactory->numOfDepartment] = pDepartment;
	pFactory->numOfDepartment++;
	return 1;
}

int AddGame(Factory* pFactory) 
{
	pFactory->GamesArr = (Game*)realloc(pFactory->GamesArr, (pFactory->numOfGames + 1) * sizeof(Game));
	if (!pFactory->GamesArr)
		return 0;
	
	if (!initGame(&pFactory->GamesArr[pFactory->numOfGames], pFactory->GamesArr, pFactory->numOfGames))
		return 0;
	pFactory->numOfGames++;
	return 1;
}

int AddCustomer(Factory* pFactory)
{
	pFactory->CustomerArr = (Customer*)realloc(pFactory->CustomerArr, (pFactory->numOfCustomers + 1) * sizeof(Customer));
	if (!pFactory->CustomerArr) 
		return 0;
	if (!initCustomer(&pFactory->CustomerArr[pFactory->numOfCustomers],pFactory))
		return 0;
	pFactory->numOfCustomers++;
	return 1;

}

double getDepartmentArrExpensesPerMonth(const Factory* pFactory)
{
	int i;
	double sum=0;
	for (i = 0;i < pFactory->numOfDepartment;i++)
	{
		sum = (sum + getDepartmentExpensesPerMonth(pFactory->DepartmentArr[i]));  
	}
	return sum;
}

double getWorkersExpesesPerMonth(const Factory* pFactory)
{
	int i;
	double sum=0;
	for (i = 0;i < pFactory->numOfWorker;i++)
	{
		sum = (sum + pFactory->WorkerArr[i]->salary);
	}
	return sum;

}

void printFactoryExpesesPerMonth(const Factory* pFactory)
{
	double electBill, WaterBill, otherBill, sum;
	printf("Enter electricity bill In Shekel: ");
	scanf("%lf", &electBill);
	printf("Enter Water bill In Shekel: ");
	scanf("%lf", &WaterBill);
	printf("Enter other expenses In Shekel: ");
	scanf("%lf", &otherBill);
	sum = Add5(electBill , WaterBill , otherBill , getWorkersExpesesPerMonth(pFactory) , getDepartmentArrExpensesPerMonth(pFactory));
	printf("All expenses for the factory is %.3f Shekel", sum);

}

int AddGameOrder(Factory* pFactory)
{
	char code[MAX_STR_LEN] ; 
	Customer* pCustomer;
	Game* pGame;
	int serialNumber,ok=0;
	printCustomerArray(pFactory);
	printf("Enter code of the Customer whitch you want to add order: ");
	getCustomerCode(code);
	printf("%s\n\n", code);
	pCustomer = findCustomerByCode(pFactory, code);
	if (pCustomer != NULL)
	{
		do {
			printGameArray(pFactory);
			printf("Enter a serial numbers of the game you want to make an order: ");
			scanf("%d", &serialNumber);
			pGame = findGameBySerialNumber(pFactory->GamesArr, pFactory->numOfGames, serialNumber);
			if (pGame != NULL)
				ok=1;
		} while (ok != 1);
		return addOrder(pCustomer, pGame);

	}
	printf("The factory did not have this Customer %s \n",code);
	return 0;
	
}

Department* getDepartment(const Factory* pFactory,char* msg)
{
	int ok = 0;
	Department* pDepartment = NULL;
	char code[CODELEN + 1];
	if (pFactory->numOfDepartment > 0)
	{
		printDepartmentWithoutMachines(pFactory); 
		do {
			
			printf("%s: ", msg);
			scanf("%s", code);
			if (checkCode(code) == 1)
			{
				pDepartment =findDepartmentByCode(code, pFactory->DepartmentArr, pFactory->numOfDepartment);
				if (pDepartment != NULL)
					ok = 1;
			}
		} while (ok != 1);
	}
	else
	{
		printf("The Factory not have a Department");
		return NULL;
	}
	printf("\n");
	return pDepartment;
}

int removeWorker(Factory* pFactory)
{ 
	Worker* pWorker =NULL; 
	Worker Worker1;
	printf("Enter Id number of Worker which You want to remove: \n"); 
	getIDNumber(&Worker1, NULL, 0);
	for (int i = 0;i < pFactory->numOfWorker;i++)
	{
		if (isIDNumber(pFactory->WorkerArr[i], Worker1.ID) == 1)   
		{
			pWorker = pFactory->WorkerArr[i]; 
		    pFactory->WorkerArr[i] = pFactory->WorkerArr[pFactory->numOfWorker - 1]; 
			pFactory->WorkerArr = (Worker**)realloc(pFactory->WorkerArr, (pFactory->numOfWorker - 1) * sizeof(Worker*)); 
			if (!pFactory->WorkerArr)
			{
				free(pWorker);
				return 0;
			}
			pFactory->numOfWorker --;
			return 1;
		}
	}
	return 0;

}

int removeGame(Factory* pFactory)
{
	Game game;
	printf("Enter Serial number of Game which You want to remove: \n");
	getSerialNumber(&game, NULL, 0);
	for (int i = 0;i < pFactory->numOfGames;i++)
	{
		if (pFactory->GamesArr[i].SerialNumber == game.SerialNumber)
		{
			pFactory->GamesArr[i] = pFactory->GamesArr[pFactory->numOfGames - 1];
			pFactory->GamesArr = (Game*)realloc(pFactory->GamesArr, (pFactory->numOfGames - 1) * sizeof(Game));
			if (!pFactory->GamesArr)
				return 0;
			pFactory->numOfGames--;
			return 1;
		}

	}
	return 0;
}

int removeCustomer(Factory* pFactory)
{
	Customer customer;
	printf("Enter Code of Customer which You want to remove: \n");
	getCustomerCode(customer.CODE);
	for (int i = 0;i < pFactory->numOfCustomers;i++)
	{
		if (strcmp(pFactory->CustomerArr[i].CODE, customer.CODE) == 0)
		{
			pFactory->CustomerArr[i] = pFactory->CustomerArr[pFactory->numOfCustomers - 1];
			pFactory->CustomerArr = (Customer*)realloc(pFactory->CustomerArr, (pFactory->numOfCustomers - 1) * sizeof(Customer));
			if (!pFactory->CustomerArr)
				return 0;
			pFactory->numOfCustomers--;
			return 1;
		}

	}
	return 0;
}

Customer* findCustomerByCode(const Factory* pFactory, const char* code)
{
	int i;
	for (i = 0;i < pFactory->numOfCustomers;i++)
	{
		if (strcmp(pFactory->CustomerArr[i].CODE, code) == 0)  
			return &pFactory->CustomerArr[i];
	}
	return NULL;
}

int checkUniqeCodeForCustomer(const Factory* pFactory,const char* code )
{
	Customer* pCustomer = findCustomerByCode(pFactory, code);

	if (pCustomer != NULL)
		return 0;

	return 1;
}

int initCustomer(Customer* pCustomer, Factory* pFactory)
{
	while (1)
	{
		getCustomerCode(pCustomer->CODE);
		if (checkUniqeCodeForCustomer(pFactory, pCustomer->CODE)) 
			break;

		printf("This code already in use - enter a different code\n");
	}

	return initCustomerWithoutCode(pCustomer); 
}


void AddMachineToDepartment(Factory* pFactory)
{
	Department* pDepartment = getDepartment(pFactory,"Enter code of Department to which you want to add a machine"); 
	AddMachine(pDepartment);
}

void AddDepartmentToWorker(Factory* pFactory,Worker* pWorker)
{
	Department* pDepartment = getDepartment(pFactory, "Enter code of Department to which you want the worker to work");
	pWorker->Department = pDepartment;
}

void showDepartmentInFactory(const Factory* pFactory)
{
	int i;
	eMaterialType Type = getMaterialType();
	for (i = 0;i < pFactory->numOfDepartment;i++)
		showMachinesByMaterialInDepartment(pFactory->DepartmentArr[i], Type);
}

void printDepartmentWithoutMachines(const Factory* pFactory)
{
	int i;
	for (i = 0;i < pFactory->numOfDepartment;i++)
	{
		printDepartmentwithouMachine(pFactory->DepartmentArr[i]); 	
	}
}

void printWorkersThatWorksInDepartment(const Factory* pFactory)
{
	Department* pDepartment = getDepartment(pFactory, "Enter code of Department to which you want to print all Workers that Works in the Department ");
	int i;
	for (i = 0;i < pFactory->numOfWorker;i++)
	{
		if (checkDepartmentCodeForWorker(pFactory->WorkerArr[i], pDepartment->DepartmentCode) == 1)
			printWorker(pFactory->WorkerArr[i]);
	}
}

eSortBy getSortBy()
{
	int option;
	printf("\n");
	printf("Base on what field do you want to sort?\n");
	do {
		for (int i = 1; i < eNofSortBy; i++)
			printf("Enter %d for %s\n", i, sortByStr[i]);
		scanf("%d", &option);
		printf("\n");
	} while (option < 0 || option >= eNofSortBy);
	getchar();
	return (eSortBy)option;
}

void sortWorkers(Factory* pFactory)
{
	pFactory->SortBy = getSortBy();
	int(*compare)(const void* worker1, const void* worker2) = NULL;
	switch (pFactory->SortBy)
	{
	case eName:
		compare = compareByName;
		break;

	case eSalary:
		compare = compareBySalary;
		break;

	case eDate:
		compare = compareByDate;
		break;
	}
	if (compare != NULL) {
		qsort(pFactory->WorkerArr, pFactory->numOfWorker, sizeof(Worker*), compare);
		printf("The workers sorted by %s", sortByStr[pFactory->SortBy]);
	}
	
}

void findWorker(const Factory* pFactory)
{
	int (*compare)(const void* worker1, const void* worker2) = NULL;
	Worker worker = { 0 };
	Worker* pWorker1 = &worker;
	switch (pFactory->SortBy)
	{
	case eName:
		printf("Full Name: ");
		getName(&worker);
		compare = compareByName;
		break;
	case eSalary:
		printf("Salary: ");
		getSalay(&worker);
		compare = compareBySalary;
		break;
	case eDate:
		printf("Date:");
		getCorrectDate(&worker.date);
		compare = compareByDate;
		break;
	}
	if (compare != NULL)
	{
		Worker** pWORKER = bsearch(&pWorker1, pFactory->WorkerArr, pFactory->numOfWorker, sizeof(Worker*), compare);
		printResultSearch(pWORKER);
	}
	else
		printf("The search cannot be performed, array not sorted");
}

void printResultSearch(const Worker** pWorker)
{
	if (pWorker == NULL)
		printf("Worker was not found\n");
	else {
		printf("\nWorker found ");
		printWorker(*pWorker); 
	}
}

void printDepartmentArray(const Factory* pFactory)
{
	generalArrayFunction(pFactory->DepartmentArr, pFactory->numOfDepartment, sizeof(Department*), printDepartmentPtr);
}

void printGameArray(const Factory* pFactory)
{
	printGameArr(pFactory->GamesArr, pFactory->numOfGames);
	
}

void printCustomerArray(const Factory* pFactory)
{
	int i;
	for (i = 0;i < pFactory->numOfCustomers; i++)
	{
		printCustomer(&pFactory->CustomerArr[i]);
	}
}

void printCustomerArrayNoOrders(const Factory* pFactory)
{
	int i;
	for (i = 0;i < pFactory->numOfCustomers; i++)
	{
		printCustomerNoOrders(&pFactory->CustomerArr[i]);
	}
}

void printMachinesInDepartment(const Factory* pFactory)
{
	Department* pDepartment = getDepartment(pFactory,"Enter code of Department to which you want to print machines");
	if (pDepartment)
		printDepartment(pDepartment);

}
void printOrdersForCustomer(const Factory* pFactory)
{
	char code[LENCODE+1];
	getCustomerCode(code);
	Customer* pCustomer = findCustomerByCode(pFactory, code);
	if (pCustomer)
		printOrders(pCustomer);
}

void printWorkerArray(const Factory* pFactory)
{
	generalArrayFunction(pFactory->WorkerArr, pFactory->numOfWorker, sizeof(Worker*), printWorkerPtr);
}

void printAllMachines(const Factory* pFactory)
{
	printf("All Machines in the Factory\n");
	int i;
	for (i = 0;i < pFactory->numOfDepartment;i++)
	{
		printMachinesArray(pFactory->DepartmentArr[i]);
	}
}

void printFactory(const Factory* pFactory)
{
	printf("The Factory Name is %s \n\nThe Factory has %d Workers\n", pFactory->FactoryName, pFactory->numOfWorker);
	printWorkerArray(pFactory);
	printf("\nThe Factory has %d Department\n",pFactory->numOfDepartment); 
	printDepartmentArray(pFactory); 
	printf("\nThe Factory Makes %d Games\n", pFactory->numOfGames);
	printGameArray(pFactory);
	printf("\nThe Factory have %d customers\n",pFactory->numOfCustomers);
	printCustomerArray(pFactory);
	
}
void freeWorkerArr(Factory* pFactory)
{
	generalArrayFunction(pFactory->WorkerArr, pFactory->numOfWorker, sizeof(Worker*), freeWorker); 
}

void freeDepartmentArr(Factory* pFactory)
{
	generalArrayFunction(pFactory->DepartmentArr, pFactory->numOfDepartment, sizeof(Department*), freeDepartment); 
}

void freeCustomersArr(Factory* pFactory) 
{
	int i;
	for (i = 0;i < pFactory->numOfCustomers;i++)
	{
		freeCustomer(&pFactory->CustomerArr[i]);
	}
}

void freeGameArr(Factory* pFactory)
{
	int i;
	for (i = 0;i < pFactory->numOfGames;i++)
	{
		freeGame(&pFactory->GamesArr[i]);
	}
}

void freeFactory(Factory* pFactory)
{
	free(pFactory->FactoryName);
	freeDepartmentArr(pFactory);
	freeWorkerArr(pFactory);
	freeGameArr(pFactory);
	freeCustomersArr(pFactory);
}