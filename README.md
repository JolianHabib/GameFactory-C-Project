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
The system is divided into multiple `.c` and `.h` files:  
- `departments.c / departments.h`  
- `workers.c / workers.h`  
- `machines.c / machines.h`  
- `materials.c / materials.h`  
- `games.c / games.h`  
- `orders.c / orders.h`  
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
2. Compile (Windows MinGW):
gcc -o GameFactory.exe *.c
GameFactory.exe

3. Using an IDE (CLion / CodeBlocks / VSCode)

Create a new C project

Copy all .c and .h files into the src folder

Build & run

🛠 Technologies Used

C Language (ANSI C)

Structs, pointers, dynamic memory

Modular programming

File I/O

Header-based architecture

📥 Folder Structure
GameFactory/
│
├── departments.c / .h
├── workers.c / .h
├── games.c / .h
├── materials.c / .h
├── machines.c / .h
├── orders.c / .h
├── main.c
└── data/
    ├── workers.txt
    ├── machines.txt
    ├── materials.txt
    ├── games.txt
    └── orders.txt

🧪 Example Capabilities

Add a new worker to a specific department

Assign a machine to a worker

Add raw materials

Check if you can build a game based on inventory

Submit a customer order

Update stock after production

Save all changes to files

📌 Academic Skills Demonstrated

This project highlights key software engineering skills:

Clean modular design

Memory management

Separation into functional modules

Real-world modeling

File-based database simulation

Problem decomposition

Working with multiple interacting C modules

👤 Author

Jolian Habib
4th-year Software Engineering Student – Afeka College
GitHub: https://github.com/JolianHabib
```
