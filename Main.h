#pragma once

#include "Factory.h"

#define EXIT			-1

typedef enum
{
	eAddDepartment, eAddWorker, eAddMachine, eAddGame, eAddCustomer,
	eAddGameOrder,eRemoveWorker,eRemoveGame,eRemoveCustomer ,ePrintFactory, ePrintWorkers, ePrintDepartments,
	ePrintDepartmentsMachines, ePrintGames,ePrintCustomers,ePrintCustomersOrders,
	ePrintAllMachines,ePrintMachinsByMaterial,ePrintWorkerInDepartment,
	ePrintFactoryExpesesPerMonth, eSortWorkers, eFindWorker, eNofOptions
} eMenuOptions;

const char* str[eNofOptions] = { "Add Department","Add Worker","Add Machine","Add Game",
                                "Add Customer","Add Game Order To customer Of The Factory",
	                            "Remove Worker","Remove Game","Remove Customer","Print Factory","Print All Workers","Print All Department",
	                            "Print Department's Machines","Print All Games","Print All Customers",
	                            "Print Customer's Orders","Print All Machines In The Factory","Print All Machines with Material Type That used",
	                            "Print All Department's Workers","Print Factory Expeses Per Month",
								"Sort Workers",
								"Find Worker" };


int menu();