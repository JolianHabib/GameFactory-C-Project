# 🎮 GameFactory – Modular C Project

A modular C-based system that simulates the management of a toy/game factory.  
The project focuses on structured programming, dynamic memory management, and file-based data handling — built fully in C without external libraries.

---

## 📌 Project Overview

The GameFactory system models a real production environment with multiple components that interact together:

- **Departments**  
  Production, packaging, materials, workers, etc.

- **Workers**  
  Each worker has an ID, name, role, department, and assigned tasks.

- **Machines**  
  Machines involved in building or assembling games, including their status and type.

- **Materials**  
  Raw materials required to build specific toys/games.

- **Games / Products**  
  Game catalog with properties such as ID, name, category, required materials, and production time.

- **Customers & Orders**  
  Customers can place orders, and the system validates stock, production flow, and availability.

---

## 🧩 Features

### 🔧 1. Modular Architecture  
The system is divided into multiple `.c` and `.h` modules, each responsible for part of the factory logic:

- `Address.c / Address.h` — Handles address details for customers and factory entities.
- `Customer.c / Customer.h` — Manages customer information and interactions.
- `Date.c / Date.h` — Utility for date handling (orders, timestamps, etc.).
- `Department.c / Department.h` — Represents and manages factory departments.
- `Factory.c / Factory.h` — Core factory logic and global data structures.
- `FactoryFile.c / FactoryFile.h` — Handles loading and saving factory data to files.
- `Game.c / Game.h` — Represents game objects and product details.
- `GameOrder.c / GameOrder.h` — Manages customer game orders and order processing.
- `General.c / General.h` — General shared utilities and helper functions.
- `GeneralList.c / GeneralList.h` — Generic linked-list or array-based list structures.
- `Machine.c / Machine.h` — Information and behaviors related to machines.
- `Main.c / Main.h` — Main program entry point and application flow.
- `Material.c / Material.h` — Raw materials and inventory management.

This separation demonstrates clean software architecture in C.

### 📁 2. File Handling (Load & Save)  
All data is read from and stored to files:  
- workers list  
- machines  
- materials  
- customer orders  
- available games  

The system loads them on startup and saves updates automatically.

### 📊 3. Dynamic Data Structures  
The project uses:
- Dynamic arrays  
- Structs  
- Nested structs  
- Pointers  
- Linked relations between entities  

### ⚙️ 4. Full Factory Workflow  
The program supports:
- Adding workers / machines / materials  
- Searching & updating entities  
- Adding new games  
- Creating customer orders  
- Checking inventory  
- Assigning production tasks  

---

## 🚀 How to Run

### **1. Compile (Linux/Mac/WSL):**

bash
gcc -o GameFactory *.c
./GameFactory
### 2. Compile (Windows MinGW):
gcc -o GameFactory.exe *.c
GameFactory.exe

### 3. Using an IDE (CLion / CodeBlocks / VSCode)

Create a new C project

Copy all .c and .h files into the src folder

Build & run

### 🛠 Technologies Used

C Language (ANSI C)

Structs, pointers, dynamic memory

Modular programming

Header-based architecture

### 📥 Folder Structure
```
GameFactory/
│
├── Address.c
├── Address.h
│
├── Customer.c
├── Customer.h
│
├── Date.c
├── Date.h
│
├── Department.c
├── Department.h
│
├── Factory.c
├── Factory.h
├── Factory.bin
├── Factory.txt
│
├── FactoryFile.c
├── FactoryFile.h
│
├── Game.c
├── Game.h
│
├── GameOrder.c
├── GameOrder.h
│
├── General.c
├── General.h
│
├── GeneralList.c
├── GeneralList.h
│
├── Machine.c
├── Machine.h
│
├── Main.c
├── Main.h
│
├── Material.c
└── Material.h
```
### 🧪 Example Capabilities

Add a new worker to a specific department

Assign a machine to a worker

Add raw materials

Check if you can build a game based on inventory

Submit a customer order

Update stock after production

Save all changes to files

### 📌 Academic Skills Demonstrated

This project highlights key software engineering skills:

Clean modular design

Memory management

Separation into functional modules

Real-world modeling

File-based database simulation

Problem decomposition

Working with multiple interacting C modules

### 👤 Author

Jolian Habib
4th-year Software Engineering Student – Afeka College
GitHub: https://github.com/JolianHabib
```
