# 🛒 C Food Store Management – Part 1

This project was developed as **Part 1** of a multi-stage assignment in the course  
**Introduction to Systems Programming (Course 10010)**, Semester A.  
It simulates the foundation of a food store system in C, including customers, products, shopping carts, and user interaction via terminal.

---

## 🎯 Project Overview

This part of the system allows:
- Adding products with name, barcode, type, and expiration date
- Creating customers with name and validated ID
- Adding products to customer carts and handling purchases
- Managing individual shopping carts (print, pay, or discard)
- Restocking products when carts are abandoned
- Validating inputs and dates
- A console-based, menu-driven interface

---

## 💡 Key Concepts

- 📦 **Modular C design** using `.c` / `.h` separation
- 🧱 **Structs**: `Product`, `Customer`, `SuperMarket`, `Date`, `ShoppingCart`, etc.
- 🔄 **Dynamic arrays** using `malloc`, `realloc`, and `free`
- 🛒 **Shopping cart system** per customer
- 🧾 **Product barcodes** and category validation
- 📅 **Date validation and comparison**
- 🛡️ **Defensive programming** with error messages and enums

---

## 📁 File Structure

| File                   | Description                                  |
|------------------------|----------------------------------------------|
| `main.c`               | Main menu and user interface                 |
| `SuperMarket.c/h`      | Core logic for managing the supermarket      |
| `Product.c/h`          | Product creation, validation, and display    |
| `Customer.c/h`         | Customer creation, input validation          |
| `ShoppingCart.c/h`     | Shopping cart logic and memory handling      |
| `ShoppingItem.c/h`     | Representation of single items in a cart     |
| `Date.c/h`             | Input validation and date management         |
| `generalFunctions.c/h` | Utility functions for input and memory       |
| `Makefile`             | Build automation file                        |

---

## 🛠️ Compilation & Execution

This project includes a `Makefile` to simplify compilation.

### 🔧 To compile:

```bash
make
```
This will compile all .c source files and generate an executable named store.

### ▶️ To run:
```bash
./store
```

### 🧹 To clean up compiled files:
```bash
make clean
```
This will remove all .o object files and the executable store.

The Makefile uses gcc with the -Wall flag and includes per-file dependencies.

### 📷 Example Menu Output:
```bash
Please choose one of the following options
0 - Show SuperMarket
1 - Add Product
2 - Add Customer
3 - Customer Shopping
4 - Print Shopping Cart
5 - Customer Shopping Cart Management
6 - Print Product By Type
-1 - Quit
```
### 🧠 What I Learned:
- Working with structs and pointer-based dynamic memory in C
- Designing modular systems using .c and .h files
- Creating menu-driven console interfaces
- Managing memory allocation and cleanup responsibly
- Implementing custom input validation and enums

### 👤 Author:
Itamar Hadad  
B.Sc. Computer Science Student – Afeka Tel Aviv Academic College of Engineering  
Email: hzitamar4@gmail.com  
LinkedIn: https://www.linkedin.com/in/itamar-hadad


