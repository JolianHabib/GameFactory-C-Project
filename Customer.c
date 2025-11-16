#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "Customer.h"
#include "Game.h"
#include "fileHelper.h"
#include "General.h" 
#include "Address.h"

int initCustomerWithoutCode(Customer* pCustomer)
{
	pCustomer->name = getStrExactName("Enter name of Customer");
	if (!pCustomer->name)
		return 0;
	initAddress(&pCustomer->address);
	if (!L_init(&pCustomer->OrdersList))
		return 0; 
	return 1;
}

int addOrder(Customer* pCustomer, const Game* pGame )
{
	GameOrder* pOrder = (GameOrder*)calloc(1, sizeof(GameOrder));
	if (!pOrder)
		return 0;

	if (!initGameOrder(pOrder,pCustomer, pGame)) 
	{
		freeOrder(pOrder); 
		return 0;
	}

	return insertNewOrderToList(&pCustomer->OrdersList, pOrder);
}

int	insertNewOrderToList(LIST* pProductList, GameOrder* pOrder) 
{
	NODE* pN = pProductList->head.next; //first Node
	NODE* pPrevNode = &pProductList->head;
	GameOrder* pTemp;
	while (pN != NULL)
	{
		pTemp = (GameOrder*)pN->key; 
		if (pTemp->serialNumber == pOrder->serialNumber)
		{
			printf("Not new Order - error!!!\n");
			return 0;
		}

		else{	
			if (!L_insert(pPrevNode, pOrder))
				return 0;
			return 1;
		}
		pPrevNode = pN;
		pN = pN->next;
	}
	//insert at end
	if (!L_insert(pPrevNode, pOrder))
		return 0;
	return 1;
}

GameOrder* findGameOrderBySerialNumber(const Customer* pCustomer, const int serialNumber)
{

	NODE* pN = pCustomer->OrdersList.head.next; //first Node
	if (!pN)
		return NULL;

	GameOrder* pTemp;
	while (pN != NULL)
	{
		pTemp = (GameOrder*)pN->key;
		if (pTemp->serialNumber == serialNumber)
			return pTemp;
		pN = pN->next;
	}

	return NULL;
}

void getCustomerCode(char* code)
{
	char temp[MAX_STR_LEN];
	int ok = 1;
	do {
		ok = 1;
		printf("Enter Customer code  - %d UPPER CASE letters: ", LENCODE);
		myGets(temp, MAX_STR_LEN, stdin);
		if (strlen(temp) != LENCODE)
		{
			printf("code should be %d letters\n",LENCODE); 
			ok = 0;
		}
		else {
			for (int i = 0; i < LENCODE; i++) 
			{
				if (isupper(temp[i]) == 0)
				{
					printf("Need to be upper case letter\n");
					ok = 0;
					break;
				}
			}
		}
	} while (!ok);

	strcpy(code, temp);
}

int checkUniqeSerialnumber(const int SerialNumber, const Customer* pCustomer)
{
	//the serial number is not used by the same customer. (the system could to make two orders with same serial number but for difrent customers.) 
	GameOrder* pOrder = findGameOrderBySerialNumber(pCustomer, SerialNumber); 

	if (pOrder != NULL)
		return 0;

	return 1;
}

int initGameOrder(GameOrder* pOrder, Customer* pCustomer,const Game* pGame)
{
	while (1)
	{
		getOrderSerialNumber(pOrder);
		if (checkUniqeSerialnumber(pOrder->serialNumber, pCustomer))
			break;
		printf("This serial number in use.\n");
	}
	return initGameOrderwithoutSerialNumber(pOrder,pGame); 
}

int	getOrderscount(const Customer* pCustomer)
{
	int count = 0;
	NODE* pN = pCustomer->OrdersList.head.next; //first Node

	while (pN != NULL)
	{
		count++;
		pN = pN->next;
	}
	return count;
}

void printOrders(const Customer* pCustomer) 
{
	int count = getOrderscount(pCustomer); 
	printf("have %d Orders\n", count);
	L_print(&pCustomer->OrdersList, printOrderV); 
	printf("\n");

}

void freeOrders(Customer* pCustomer)
{
	L_free(&pCustomer->OrdersList, freeOrderV);
}

int	saveCustomerToBinaryFile(const Customer* pCustomer, FILE* fp) 
{
	if (!writeStringToFile(pCustomer->name, fp, "Error write Customer Name.\n"))
		return 0;
	if (!saveAddressToBinaryFile(&pCustomer->address, fp))
		return 0;
	if (!writeCharsToFile(pCustomer->CODE, LENCODE, fp, "Error write CustomerCode.\n"))
		return 0;
	int count = getOrderscount(pCustomer) ;
	if (!writeIntToFile(count, fp, "Error write Orders count.\n"))
		return 0;
	if (count > 0)
	{
		NODE* pN = pCustomer->OrdersList.head.next; //first Node

		GameOrder* pTemp; 
		while (pN != NULL)
		{
			pTemp = (GameOrder*)pN->key; 
			if (!saveOrderToBinaryFile(pTemp, fp)) 
			{
				printf("Error write Order\n");
				return 0;
			}
			pN = pN->next;
		}
	}
	return 1;

}

int	loadCustomerFromBinaryFile(Customer* pCustomer, FILE* fp)
{
	int count; 
	pCustomer->name = readStringFromFile(fp, "Error reading Customer name.\n");
	if (!pCustomer->name)
		return 0;
	if(!loadAddressFromBinaryFile(&pCustomer->address,fp))
		return 0;
	if (!readCharsFromFile(pCustomer->CODE, LENCODE, fp, "Error reading Customer code.\n"))
		return 0;
	if (!readIntFromFile(&count, fp, "Error reading Order count\n"))
		return 0;
	GameOrder* pOrder;
	for (int i = 0; i < count; i++)
	{
		pOrder = (GameOrder*)calloc(1, sizeof(GameOrder)); 
		if (!pOrder) 
			break;
		if (!loadOrderFromBinaryFile(pOrder, fp))  
		{
			printf("Error loading Game Order from file\n");
			return 0;
		}
		insertNewOrderToList(&pCustomer->OrdersList, pOrder); 
	}

	return 1;

}

int saveCustomerToFile(const Customer* pCustomer, FILE* fp)
{
	if (!pCustomer)
		return 0;
	fprintf(fp, "%s\n", pCustomer->name);
	if (!saveAddressToFile(&pCustomer->address, fp))
		return 0;
	fprintf(fp, "%s\n", pCustomer->CODE);
	int count = getOrderscount(pCustomer); 
	fprintf(fp, "%d\n", count);
	if (count > 0)
	{ 
		NODE* pN = pCustomer->OrdersList.head.next; //first Node 

		GameOrder* pTemp;
		while (pN != NULL)
		{
			pTemp = (GameOrder*)pN->key;
			if (!saveOrderToFile(pTemp, fp)) 
			{
				printf("Error write Order\n");
				return 0;
			}
			pN = pN->next;
		}
	}
	return 1;
}

int loadCustomerFromFile(Customer* pCustomer, FILE* fp)
{
	int count;
	if (!pCustomer)
		return 0;
	pCustomer->name = readDynStringFromTextFile(fp);
	if (!loadAddressFromFile(&pCustomer->address, fp))
		return 0;
	fscanf(fp, "%s", &pCustomer->CODE);
	fscanf(fp, "%d", &count); 
	fgetc(fp);  //clean the buffer
	GameOrder* pOrder;
	for (int i = 0; i < count; i++)
	{
		pOrder = (GameOrder*)calloc(1, sizeof(GameOrder)); 
		if (!pOrder) 
			break;
		if (!loadOrderFromFile(pOrder, fp))  
		{
			printf("Error loading Order from file\n");
			return 0;
		}
		insertNewOrderToList(&pCustomer->OrdersList, pOrder); 
	}
	return 1;

}


void freeCustomer(Customer* pCustomer) 
{
	free(pCustomer->name);
    L_free(&pCustomer->OrdersList, freeOrderV);
	freeAddress(&pCustomer->address);
}

void printCustomer(const Customer* pCustomer)
{
	printf("Customer: name of Customer %s his/her Code is %s\n", pCustomer->name,pCustomer->CODE);
	printAddress(&pCustomer->address);
	if (getOrderscount(pCustomer) > 0)
		printOrders(pCustomer);
	else
		printf("\n");
}

void printCustomerNoOrders(const Customer* pCustomer)
{
	printf("Customer: name of Customer %s his/her Code is %s\n", pCustomer->name, pCustomer->CODE);
	printAddress(&pCustomer->address);
	printf("\n");
}

