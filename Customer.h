#pragma once
#include "Address.h"
#include "GeneralList.h"
#include "GameOrder.h"

#define LENCODE 4
typedef struct
{
	char*		name;
	Address		address;
	char		CODE[LENCODE + 1];  
	LIST        OrdersList;
} Customer;


int initCustomerWithoutCode(Customer* pCustomer);
int	saveCustomerToBinaryFile(const Customer* pCustomer, FILE* fp);
int	loadCustomerFromBinaryFile(Customer* pCustomer, FILE* fp);
int saveCustomerToFile(const Customer* pCustomer, FILE* fp);
void getCustomerCode(char* code);
int initGameOrder(GameOrder* pOrder, Customer* pCustomer,const Game* pGame); 
GameOrder* findGameOrderBySerialNumber(const Customer* pCustomer, const int serialNumber);
int loadCustomerFromFile(Customer* pCustomer, FILE* fp);
int	insertNewOrderToList(LIST* pProductList, GameOrder* pOrder);
void printOrders(const Customer* pCustomer);
int addOrder(Customer* pCustomer, const Game* pGame);
int checkUniqeSerialnumber(const int SerialNumber, const Customer* pCustomer);
int	getOrderscount(const Customer* pCustomer);
void freeCustomer(Customer* pCustomer);
void printCustomer(const Customer* pCustomer); 
void freeOrders(Customer* pCustomer);
void printCustomerNoOrders(const Customer* pCustomer);