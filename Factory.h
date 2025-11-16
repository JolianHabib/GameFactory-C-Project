#pragma once
#include "Worker.h"
#include "Customer.h"

typedef enum { eNone, eName, eSalary, eDate, eNofSortBy }eSortBy;
static const char* sortByStr[eNofSortBy] = { "None", "Name", "Salary", "Date" };


typedef struct
{
	char* FactoryName;
	Worker** WorkerArr;
	int numOfWorker;
	Department** DepartmentArr;
	int numOfDepartment;
	Game* GamesArr;
	int numOfGames;
	Customer* CustomerArr;
	int numOfCustomers;
	eSortBy SortBy;
} Factory;

int initFactory(Factory* pFactory); 
int AddWorker(Factory* pFactory);
int AddDepartment(Factory* pFactory);
int AddGame(Factory* pFactory);
int AddCustomer(Factory* pFactory);
Department* getDepartment(const Factory* pFactory, char* msg);
void AddDepartmentToWorker(Factory* pFactory, Worker* pWorker);
void AddMachineToDepartment(Factory* pFactory);
void printFactory(const Factory* pFactory);
void sortWorkers(Factory* pFactory);
eSortBy getSortBy();
Customer* findCustomerByCode(const Factory* pFactory, const char* code);
int AddGameOrder(Factory* pFactory);
int checkUniqeCodeForCustomer(const Factory* pFactory, const char* code);
int  initCustomer(Customer* pCustomer, Factory* pFactory);
void findWorker(const Factory* pFactory);
void printWorkersThatWorksInDepartment(const Factory* pFactory);
double getDepartmentArrExpensesPerMonth(const Factory* pFactory);
double getWorkersExpesesPerMonth(const Factory* pFactory);
void printFactoryExpesesPerMonth(const Factory* pFactory);
void showDepartmentInFactory(const Factory* pFactory);
void printDepartmentArray(const Factory* pFactory);
void printCustomerArray(const Factory* pFactory);
void printGameArray(const Factory* pFactory);
void printWorkerArray(const Factory* pFactory);
void printOrdersForCustomer(const Factory* pFactory);
void printDepartmentWithoutMachines(const Factory* pFactory);
void printCustomerArrayNoOrders(const Factory* pFactory);
void printMachinesInDepartment(const Factory* pFactory);
void printResultSearch(const Worker** pWorker);
void printAllMachines(const Factory* pFactory);
void freeWorkerArr(Factory* pFactory);
int removeWorker(Factory* pFactory);
int removeGame(Factory* pFactory);
int removeCustomer(Factory* pFactory);
void freeDepartmentArr(Factory* pFactory);
void freeCustomersArr(Factory* pFactory);
void freeGameArr(Factory* pFactory);
void freeFactory(Factory* pFactory);