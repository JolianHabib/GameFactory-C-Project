# Game Factory Management System

This project is a C language console application that manages a **game factory**.  
The system stores and manages information about workers, departments, machines, materials, customers and game orders, and allows the user to perform many operations on this data.

The project was written in pure C using structs, dynamic memory, pointers, linked lists and binary files.


## Main Features

The system allows the user to:

- Add a **department** to the factory.
- Add a **worker** to the factory (only if there is at least one department).
- Add a **machine** to a specific department, by department code.
- Add a **game** that the factory produces.
- Add a **customer** to the factory.
- Add a **game order** for an existing customer, by game serial number.
- Delete a **worker** by ID number.
- Delete a **game** by its serial number.
- Delete a **customer** by his customer code.
- Print **all factory data**: factory name, workers, departments and their machines, games, customers and their orders.
- Print all **workers** in the factory.
- Print all **departments** in the factory.
- Print all **machines** in a specific department.
- Print all **games** in the factory.
- Print all **customers** in the factory.
- Print all **orders** of a specific customer.
- Print all **machines** in the factory.
- Print all machines that use a **specific material**.
- Print all workers that belong to a **specific department**.
- Calculate and print the **monthly expenses** of the factory (workers’ salaries, department expenses, electricity, water, other expenses).
- **Sort workers** by:
  - name (lexicographic),
  - salary,
  - start date.
- **Search workers** by:
  - name,
  - salary,
  - start date (binary search).


## Data Structures

The project is built around several main structs:

- `Material` – describes raw material used by machines  
  - price per 1 kg  
  - rank  
  - material type (plastic, carton, wood, rubber, etc.)

- `Machine` – describes a machine inside a department  
  - serial number  
  - `Material`  
  - amount of material used per month (in kg)

- `Department` – describes a department in the factory  
  - department name  
  - unique department code (2 chars: first is a letter, second is a digit)  
  - dynamic array of machines and number of machines

- `Worker` – describes a worker in the factory  
  - name  
  - ID number (9 chars, unique)  
  - monthly salary  
  - address  
  - start work date  
  - pointer to the department where the worker works  
  - department code

- `Game` – describes a game that the factory produces  
  - game name  
  - unique serial number  
  - price  
  - game type (thinking game, kids game, baby game, chance game, board game, target game)

- `GameOrder` – describes an order of a game by a customer  
  - game  
  - quantity  
  - serial number of the order  
  - total price (calculated from quantity and game price)

- `Customer` – describes a customer of the factory  
  - name  
  - address  
  - unique customer code (4 capital letters)  
  - linked list of the customer’s orders

- `Factory` – the main struct that contains everything  
  - factory name  
  - array of workers + number of workers  
  - array of departments + number of departments  
  - array of games + number of games  
  - array of customers + number of customers


## Binary File Format (Material)

The project also includes an example of **compressed binary storage** for the `Material` struct.

`Material` is saved to a binary file using a packed format:

- `type` (material type) – 1 bit  
- `rank` – 1 bit  
- `price` – 14 bits  

After that, the `rank` character is written.

This shows how to work with bit operations and compact binary formats in C.


## Important Functions (Examples)

Some of the important functions implemented in the project:

### Worker

- `isIDNumber` – checks if a given ID string belongs to a specific worker.
- `findWorkerById` – searches an array of workers by ID and returns a pointer to the worker (or `NULL`).
- `compareByName`, `compareBySalary`, `compareByDate` – comparison functions for sorting.
- `checkDepartmentCodeForWorker` – checks if a worker belongs to a given department code.

### Customer

- `addOrder` – adds a new order to the customer (linked list).
- `findGameOrderBySerialNumber` – finds an order by its serial number.

### Machine

- `showMachineByMaterial` – returns / prints the type of material used by the machine.
- `getMachineExpensesPerMonth` – calculates the monthly expenses of a machine.

### Department

- `checkUniqueCode` – validates that department code is legal and unique.
- `addMachine` – adds a machine to the department.
- `findDepartmentByCode` – searches a department array by code.

### Factory

- `addCustomer`, `addDepartment`, `addWorker`, `addGame` – add entities to the factory.
- `removeGame`, `removeWorker`, `removeCustomer` – delete entities from the factory.
- `getDepartmentArrExpensesPerMonth` – calculates total expenses of the factory.
- `sortWorkers` – sorts workers by chosen property (name, salary, date).
- `findWorker` – searches workers by name, salary or date (binary search).
- `showDepartmentInFactory` – prints all machines that work with a specific material.


## Project Structure

The code is split into header (`.h`) and source (`.c`) files, for example:

- `Material.h`, `Material.c`
- `Machine.h`, `Machine.c`
- `Department.h`, `Department.c`
- `Worker.h`, `Worker.c`
- `Game.h`, `Game.c`
- `GameOrder.h`, `GameOrder.c`
- `Customer.h`, `Customer.c`
- `Factory.h`, `Factory.c`
- `Date.h`, `Date.c`
- `Address.h`, `Address.c`
- `main.c`

Each header file uses `#pragma once` and contains the struct definition and function declarations.  
Each `.c` file contains the implementation.


## How to Build and Run

### Visual Studio (Windows)

1. Open the solution or create a new **Empty Project** in Visual Studio.
2. Add all `.c` and `.h` files to the project (Source Files / Header Files).
3. Make sure `main.c` is part of the project and contains the `main()` function.
4. Place `Factory.txt` and `Factory.bin` in the project folder.
5. Build the project: **Build → Build Solution**.
6. Run the program: **Debug → Start Without Debugging** (or `Ctrl + F5`).

### GCC (command line)

If you use gcc:

```bash
gcc -Wall -std=c99 -o factory main.c Factory.c Worker.c Department.c \
    Machine.c Material.c Game.c GameOrder.c Customer.c Date.c Address.c
./factory
