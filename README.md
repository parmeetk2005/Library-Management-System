# 📚 Library Management System

A clean, modular C++ command-line application for managing a book library.

---

## 📂 Project Structure

```
LibraryManagementSystem/
│
├── src/
│   ├── main.cpp        ← Entry point & CLI loop
│   ├── Library.cpp     ← Library class implementation
│   └── Book.cpp        ← Book class implementation
│
├── include/
│   ├── Library.h       ← Library class declaration
│   └── Book.h          ← Book class declaration
│
├── data/
│   └── books.txt       ← Persistent book storage (auto-created)
│
└── README.md
```

---

## 🚀 Features

| Command       | Description                          |
|---------------|--------------------------------------|
| Add Book      | Add a new book with title and author |
| List Books    | Display all books with status        |
| Borrow Book   | Mark a book as borrowed by ID        |
| Return Book   | Mark a borrowed book as returned     |
| Search Book   | Case-insensitive search by title     |
| Exit          | Save data and quit                   |

---

## 🛠 Compilation

### Using g++ directly

From the project root directory:

```bash
g++ -std=c++17 -Wall -Wextra \
    src/main.cpp src/Book.cpp src/Library.cpp \
    -I include \
    -o library_system
```

### Run the program

```bash
./library_system
```

> **Note:** Make sure the `data/` directory exists before running. The program reads and writes `data/books.txt` for persistence.

```bash
mkdir -p data
```

---

## ⭐ Example Session

```
  ╔══════════════════════════════════════╗
  ║       Library Management System      ║
  ╠══════════════════════════════════════╣
  ║  1.  Add Book                        ║
  ║  2.  List Books                      ║
  ║  3.  Borrow Book                     ║
  ║  4.  Return Book                     ║
  ║  5.  Search Book                     ║
  ║  6.  Exit                            ║
  ╚══════════════════════════════════════╝

  Your choice: 1

  ── Add New Book ──
  Enter title  : The C++ Programming Language
  Enter author : Bjarne Stroustrup
  --------------------------------------------------
  Book added successfully!
  Assigned ID : 6
  Title       : The C++ Programming Language
  Author      : Bjarne Stroustrup
  --------------------------------------------------

  Your choice: 2

  ==================================================
  LIBRARY CATALOG  (6 books | 1 borrowed)
  ==================================================
  ID     : 1
  Title  : The Pragmatic Programmer
  Author : Andrew Hunt & David Thomas
  Status : [ Available ]
  --------------------------------------------------
  ...

  Your choice: 3

  ── Borrow a Book ──
  Enter Book ID : 1
  You have borrowed: "The Pragmatic Programmer"

  Your choice: 6

  Goodbye! Your data has been saved. 👋
```

---

## 🔮 Design Decisions

- **OOP**: `Book` encapsulates a single record; `Library` manages the collection.
- **Persistence**: Data is loaded from `data/books.txt` on startup and saved automatically on exit via the destructor.
- **Serialization format**: Pipe-delimited (`id|title|author|borrowed`) for simplicity and readability.
- **Input validation**: All user inputs are validated; invalid integers or empty strings are rejected with clear messages.
- **Case-insensitive search**: Title search is lowercased before comparison for better UX.
- **STL only**: No third-party dependencies — uses `std::map`, `std::vector`, `std::string`, `std::fstream`, `std::algorithm`.

---

## 🖥 Requirements

- C++17 or later
- g++ (GCC) or clang++

