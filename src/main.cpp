#include "../include/Library.h"
#include <iostream>
#include <string>
#include <limits>
#include <sstream>

// UI helpers

static void pause() {
    std::cout << "\n  Press ENTER to continue...";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

static void printHeader() {
    std::cout << "\n";
    std::cout << "  ╔══════════════════════════════════════╗\n";
    std::cout << "  ║       Library Management System      ║\n";
    std::cout << "  ╠══════════════════════════════════════╣\n";
    std::cout << "  ║  1.  Add Book                        ║\n";
    std::cout << "  ║  2.  List Books                      ║\n";
    std::cout << "  ║  3.  Borrow Book                     ║\n";
    std::cout << "  ║  4.  Return Book                     ║\n";
    std::cout << "  ║  5.  Search Book                     ║\n";
    std::cout << "  ║  6.  Exit                            ║\n";
    std::cout << "  ╚══════════════════════════════════════╝\n";
    std::cout << "\n";
}

// Safe integer input

static int readInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return value;
        }
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        std::cout << "  [Invalid] Please enter a whole number.\n";
    }
}

// Safe non-empty string input
static std::string readString(const std::string& prompt) {
    std::string value;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, value);
        // Trim leading/trailing spaces
        auto start = value.find_first_not_of(" \t");
        auto end   = value.find_last_not_of(" \t");
        if (start != std::string::npos) {
            value = value.substr(start, end - start + 1);
            return value;
        }
        std::cout << "  [Invalid] Input cannot be empty.\n";
    }
}

// Menu handlers

static void handleAddBook(Library& lib) {
    std::cout << "\n  ── Add New Book ──\n";
    std::string title  = readString("  Enter title  : ");
    std::string author = readString("  Enter author : ");
    lib.addBook(title, author);
}

static void handleListBooks(const Library& lib) {
    std::cout << "\n";
    lib.listBooks();
}

static void handleBorrowBook(Library& lib) {
    std::cout << "\n  ── Borrow a Book ──\n";
    int id = readInt("  Enter Book ID : ");
    lib.borrowBook(id);
}

static void handleReturnBook(Library& lib) {
    std::cout << "\n  ── Return a Book ──\n";
    int id = readInt("  Enter Book ID : ");
    lib.returnBook(id);
}

static void handleSearchBook(const Library& lib) {
    std::cout << "\n  ── Search by Title ──\n";
    std::string query = readString("  Enter search term : ");
    lib.searchBookByTitle(query);
}

// Main

int main() {
    Library library("data/books.txt");

    while (true) {
        printHeader();
        int choice = readInt("  Your choice: ");

        switch (choice) {
            case 1: handleAddBook(library);    break;
            case 2: handleListBooks(library);  break;
            case 3: handleBorrowBook(library); break;
            case 4: handleReturnBook(library); break;
            case 5: handleSearchBook(library); break;
            case 6:
                std::cout << "\n  Goodbye! Your data has been saved. 👋\n\n";
                return 0;
            default:
                std::cout << "  [Invalid] Please enter a number between 1 and 6.\n";
        }

        pause();
    }

    return 0;
}
