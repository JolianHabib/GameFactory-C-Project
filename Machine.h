#pragma once
#include "Material.h"
#define MIN_SN 1
#define MAX_SN 999

typedef struct
{
	int			SerialNumber;
	Material	Material; //the material the Machine used.
	double		amount; //amount of material in kg the Machine used in a month.

} Machine;

void initMachine(Machine* pMachine, const Machine** MachineArr, const int numOfMachines);
int checkSerialNumberinClass(const int serialNumber, const Machine** MachineArr, const int numOfMachines);
void getSerialNumer(Machine* pMachine, const Machine** MachineArr, const int numOfMachines);
void getAmountOfMaterial(Machine* pMachine);
void showMachineByMetrial(const Machine* pMachine, const eMaterialType Type);  
double getMachineExpensesPerMonth(const Machine* pMachine);
int saveMachineToBinaryFile(const Machine* pMachine, FILE* fp);
int loadMachineFromBinaryFile(Machine* pMachine, FILE* fp);
int saveMachineToFile(const Machine* pMachine, FILE* fp);
int loadMachineFromFile(Machine* pMachine, FILE* fp);
void printMachine(const Machine* pMachine);
void printMachinePtr(void* elment);
void freeMachinePtr(void* elment);


