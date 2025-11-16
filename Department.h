#pragma once
#include "Machine.h"
#define CODELEN 2   
 

typedef struct
{
	char*		DepartmentName;
	char		DepartmentCode[CODELEN+1];
	Machine**   MachineArr;
	int			numOfMachines;

} Department;

int initDepartment(Department* pDepartment,const Department** DepartmentArr,const int numOfDepartment);
int AddMachine(Department* pDepartment);
Department* findDepartmentByCode(char* code, Department** DepartmentArr,const int numOfDepartment);
int checkUniqeCode( char* code, Department** DepartmentArr,const int numOfDepartment);
double getDepartmentExpensesPerMonth(const Department* pDepartment);
int checkCode(const char* code);
int saveDepartmentToBinaryFile(const Department* pDepartment, FILE* fp);
int createMachineArr(Department* pDepartment);
int loadDepartmentFromBinaryFile(Department* pDepartment, FILE* fp); 
int saveDepartmentToFile(const Department* pDepartment, FILE* fp);
int loadDepartmentFromFile(Department* pDepartment, FILE* fp);
void freeMachinestArr(Machine** arr, int size);
void showMachinesByMaterialInDepartment(const Department* pDepartment,const eMaterialType Type); 
void getDepartmentCode(Department* pDepartment, const Department** DepartmentArr,const int numOfDepartment);
void freeDepartment(void* elment);
void printMachinesArray(const Department* pDepartment);
void printDepartment(const Department* pDepartment);
void printDepartmentwithouMachine(const Department* pDepartment);
void printDepartmentPtr(void* elment);