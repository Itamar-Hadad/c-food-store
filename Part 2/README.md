# 🛒 C Food Store Management – Part 2

This project was developed as **Part 2** of a multi-stage assignment in the course  
**Introduction to Systems Programming (Course 10010)**, Semester A.  
It expands the food store system from Part 1 by introducing file handling, dynamic memory structures, linked lists, and polymorphic behavior using function pointers.

---

## 🆕 What's New in Part 2

- 📁 **File I/O**:
  - Load and save customers to text file (`Customers.txt`)
  - Save and load supermarket products in binary format

- 🔁 **Linked list implementation**:
  - Shopping carts now use a linked list
  - Items are inserted in order (by barcode)

- 👥 **Customer inheritance-like design**:
  - Two types of customers: `Customer` and `Member` (club member)
  - Members receive special discounts

- 🧠 **Polymorphism using function pointers**:
  - Virtual function behavior using `VTable.h`
  - Supports dynamic actions for printing, pricing, memory cleanup, and file saving

---

## 💡 Key Concepts

- 🔗 Linked list structures via `list.c/h`
- 🧾 File handling: read/write from both text and binary files
- 🧱 Simulated inheritance using structs and function pointers
- 🛍️ Polymorphic behavior at runtime
- 📦 Dynamic arrays of product pointers (`Product**`)
- 🧠 Modular design with `.c/.h` separation

---

## 📁 File Structure

| File                 | Description                                              |
|----------------------|----------------------------------------------------------|
| `main.c/h`           | Program entry and menu logic                             |
| `Customer.c/h`       | Base customer logic and interface                        |
| `member.c/h`         | Extended behavior for club members                       |
| `VTable.h`           | Virtual function table definition                        |
| `Product.c/h`        | Product management and binary file I/O                   |
| `Supermarket.c/h`    | System logic for loading, saving, and managing entities  |
| `ShoppingCart.c/h`   | Cart logic using linked lists                            |
| `ShoppingItem.c/h`   | Cart item representation                                 |
| `Date.c/h`           | Date validation functions                                |
| `General.c/h`        | Utilities (memory, strings, input)                       |
| `list.c/h`           | Generic linked list implementation                       |
| `Customers.txt`      | Input text file with sample customers                    |

---

## 📷 Example Menu Output:
```bash
Please choose one of the following options
0  - Show SuperMarket
1  - Add Product
2  - Add Customer
3  - Customer Shopping
4  - Print Shopping Cart
5  - Customer Shopping Cart Management
6  - Print Product By Type
7  - Save SuperMarket to file
8  - Load SuperMarket from file
9  - Save Customers to text file
10 - Load Customers from text file
11 - Print all customers
-1 - Quit
```
### 🧠 What I Learned:
- How to simulate inheritance and polymorphism in C
- Building virtual function tables (VTables) using function pointers
- Managing dynamic memory with linked lists
- Working with file I/O in text and binary formats
- Designing modular, scalable systems in C

### 👤 Author:
Itamar Hadad  
B.Sc. Computer Science Student – Afeka Tel Aviv Academic College of Engineering  
Email: hzitamar4@gmail.com  
LinkedIn: https://www.linkedin.com/in/itamar-hadad


