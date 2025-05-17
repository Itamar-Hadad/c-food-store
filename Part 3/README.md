# 🛒 C Food Store Management – Part 3

This project was developed as **Part 3** of a multi-stage assignment in the course  
**Introduction to Systems Programming (Course 10010)**, Semester A.  
It builds on the previous parts by introducing compressed file saving, generic linked lists, macro-based error handling, command-line arguments, and polymorphism in C.

---

## 🆕 What's New in Part 3

- 🗜️ Compressed binary saving using bit-level encoding
- 🧠 Macros for safe memory and file handling (`CHECK_RETURN_0`, etc.)
- 🔁 Generic linked list module (`GeneralList.c/h`) using `void*`
- 💬 Variadic function: `printMessage(...)`
- 📂 File helper module (`FileHelper.c/h`) for text & binary files
- 👥 ClubMember struct with seniority-based discount logic
- 🧾 Command-line arguments for save mode (compressed or not)

---

## 💡 Key Concepts

- Bit-level binary I/O and data packing
- Variadic functions in C
- Macros for error-safe programming
- Simulated inheritance via structs and function pointers
- Generic linked list design with `void*`
- Command-line parsing with `argc/argv`
- Clean modular code separation

---

## 📁 File Structure

| File Name              | Description                                                  |
|------------------------|--------------------------------------------------------------|
| `main.c`, `main.h`     | Entry point, menu, argument parsing                          |
| `Customer.c`, `Customer.h`     | Regular customer implementation                     |
| `ClubMember.c`, `ClubMember.h` | Members with discount logic based on seniority      |
| `Product.c`, `Product.h`       | Product logic, including barcode & binary compression |
| `Supermarket.c`, `Supermarket.h` | Overall store logic: loading, saving, managing    |
| `SuperFile.c`, `SuperFile.h`   | Compressed binary read/write logic                  |
| `ShoppingCart.c`, `ShoppingCart.h` | Cart using generic list                        |
| `ShoppingItem.c`, `ShoppingItem.h` | Cart item data and functions                   |
| `Date.c`, `Date.h`     | Date struct and compressed 2-byte encoding                   |
| `General.c`, `General.h`       | Utility functions (e.g., memory, input)             |
| `GeneralList.c`, `GeneralList.h` | Generic linked list module                        |
| `FileHelper.c`, `FileHelper.h` | Functions for reading/writing from/to files         |
| `vtable.h`             | Polymorphism using function pointers                         |
| `myMacros.h`           | Defensive macros for safer code                              |
| `Customers.txt`        | Sample text file with customer data                          |
| `SuperMarket_Compress.bin` | Sample compressed binary data file                   |

---

## 🛠️ Compilation & Execution

### 🔧 To compile manually:
```bash
gcc -o store \
main.c Customer.c ClubMember.c Product.c Supermarket.c SuperFile.c \
ShoppingCart.c ShoppingItem.c Date.c General.c GeneralList.c FileHelper.c
```

## 📷 Example Menu Output:
```bash
Please choose one of the following options
0  - Show SuperMarket
1  - Add Product
2  - Add Customer
3  - Customer Shopping
4  - Print Shopping Cart
5  - Customer Shopping Cart Management
6  - Sort Products
7  - Search Product
8  - Print Product By Type
-1 - Quit
```

## 🧠 What I Learned:
- How to design a compressed binary format with bit-level operations
- Implementing generic linked lists in C using void pointers
- Using function pointers for polymorphism-like behavior
- Applying defensive macros to simplify error handling
- Parsing program arguments and supporting flexible execution
- Creating variadic functions and clean modular separation

## 👤 Author:
Itamar Hadad  
B.Sc. Computer Science Student – Afeka Tel Aviv Academic College of Engineering  
Email: hzitamar4@gmail.com  
LinkedIn: https://www.linkedin.com/in/itamar-hadad


