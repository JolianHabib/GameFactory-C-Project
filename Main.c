#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Main.h" 
#include "Factory.h"
#include "FactoryFile.h"  
#include "Customer.h"
#include "General.h"


 
int main() 
{
	
	int fileFlag, ok = 0;
	Factory factory;
	do {
		printf("Enter 1 to init the Factory from text file, 2 to init the factory from binary file. ");
		scanf("%d", &fileFlag);
		switch (fileFlag)
		{
		case 1:
			if (!initFactoryFromFile(&factory, "Factory.txt"))
			{
				printf("error init");
				return;
			}
			ok = 1;
			break;
		
		case 2: 
			if (!initFactoryFromBinaryFile(&factory, "Factory.bin"))

			{
				printf("error init");
				return;
			}
			ok = 1;
			break;
		default:
			printf("Wrong option\n");
			break;
		}
		
	} while (ok != 1);
	
	
	//initFactory(&factory); 
	int option;
	int stop = 0; 
	do
	{
		option = menu();
		switch (option)
		{
		case eAddDepartment: 
			if (!AddDepartment(&factory))
				printf("Error adding Department\n");
			break;

		case eAddWorker: 
			if (!AddWorker(&factory)) 
				printf("Error adding Worker\n");
			break;

		case eAddMachine: 
			AddMachineToDepartment(&factory);
			break;

		case eAddGame: 
			if(!AddGame(&factory))
				printf("Error adding Game\n");
			break;

		case eAddCustomer: 
			if(!AddCustomer(&factory))
				printf("Error adding Customer\n");
			break;

		case eAddGameOrder:
			if(!AddGameOrder(&factory))
				printf("Error adding Game Order\n");
			break;
        
		case eRemoveWorker:
			if (!removeWorker(&factory))
				printf("Error removing Worker\n");
			break;

		case  eRemoveGame:
			if (!removeGame(&factory))
				printf("Error Removing Game\n");
			break;

		case eRemoveCustomer:
			if (!removeCustomer(&factory))
				printf("Error removing Customer\n");
			break;

		case ePrintFactory: 
			printFactory(&factory);
			break;

		case ePrintWorkers:
			printWorkerArray(&factory); 
			break;

		case ePrintDepartments:
			printDepartmentWithoutMachines(&factory);
			break;

		case ePrintDepartmentsMachines:
			printMachinesInDepartment(&factory);
			break;

		case ePrintGames:
			printGameArray(&factory);
			break;

		case ePrintCustomers: 
			printCustomerArrayNoOrders(&factory); 
			break;

		case ePrintCustomersOrders:
			printOrdersForCustomer(&factory);
			break;

		case ePrintAllMachines:
			printAllMachines(&factory);
			break;

		case ePrintMachinsByMaterial:
			showDepartmentInFactory(&factory);
			break;

		case ePrintWorkerInDepartment:
			printWorkersThatWorksInDepartment(&factory);
			break;

		case ePrintFactoryExpesesPerMonth:
			printFactoryExpesesPerMonth(&factory);
			break;

		case eSortWorkers:
			sortWorkers(&factory);
			break;

		case eFindWorker:
			findWorker(&factory);
			break;

		case EXIT:
			printf("Bye bye\n");
			stop = 1;
			break;

		default:
			printf("Wrong option\n");
			break;
		}
	} while (!stop);

	saveFactoryToBinaryFile(&factory,"Factory.bin");  
	saveFactoryToTextFile(&factory, "Factory.txt");
	freeFactory(&factory);
	return 0;
}


int menu()
{
	int option;
	printf("\n\n");
	printf("Please choose one of the following options\n");
	for (int i = 0; i < eNofOptions; i++) 
		printf("%d - %s\n", i, str[i]);
	printf("%d - Quit\n", EXIT);
	scanf("%d", &option);
	//clean buffer
	char tav;
	scanf("%c", &tav);
	return option;
}