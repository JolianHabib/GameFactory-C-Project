#pragma once
#include "Address.h"
#include "Date.h"
#include "Department.h"
#define IDLEN 9

typedef struct
{
	char*    name;
	char	 ID[IDLEN+1];
	Address	 address;
	double   salary;
	Department* Department; 
	char code[CODELEN + 1];
	Date     date;

} Worker;

void getSalay(Worker* pWorker); 
int	isIDNumber(const Worker* pWorker, const char* IDNumber);
int checkDigitId(const char* temp);
int checkDepartmentCodeForWorker(Worker* pWorker, char* DepartmentCode);
int checkUniqeId(Worker** workerArr,const int numOfWorker,const char* ID); 
void getIDNumber(Worker* pWorker,const Worker** WorkerArr,const int numOfWorker); 
int	initWorkerWithoutDepartment(Worker* pWorker,const Worker** WorkerArr,const int numOfWorker);
int getName(Worker* pWorker);
void printWorker(const Worker* pWorker);
Worker* findWorkerById(Worker** workerArr,const int numOfWorkerconst,const char* ID);
int compareByName(const void* worker1, const void* worker2);
int compareBySalary(const void* worker1, const void* worker2);
int compareByDate(const void* worker1, const void* worker2);
int saveWorkerToBinaryFile(const Worker* pWorker, FILE* fp);
int loadWorkerFromBinaryFile(Worker* pWorker, FILE* fp);
int saveWorkerToFile(const Worker* pWorker, FILE* fp);
int loadWorkerFromFile(Worker* pWorker, FILE* fp);
void freeWorker(void* elment);
void printWorkerPtr(void* elment);