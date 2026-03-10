#include "../include/Library.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <stdexcept>

// Helpers / internal

static void printDivider(char c = '-', int width = 50) {
    std::cout << std::string(width, c) << "\n";
}

// Constructor / Destructor

Library::Library(const std::string& filePath)
    : nextId(1), dataFilePath(filePath)
{
    loadFromFile();
}

Library::~Library() {
    saveToFile();
}

// Private: file I/O

void Library::loadFromFile() {
    std::ifstream file(dataFilePath);
    if (!file.is_open()) return;   // first run – file doesn't exist yet

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) continue;
        try {
            Book b = Book::deserialize(line);
            books[b.getId()] = b;
            if (b.getId() >= nextId)
                nextId = b.getId() + 1;
        } catch (const std::exception& e) {
            std::cerr << "[Warning] Skipping corrupted record: " << e.what() << "\n";
        }
    }
}

void Library::saveToFile() const {
    std::ofstream file(dataFilePath);
    if (!file.is_open()) {
        std::cerr << "[Error] Could not write to " << dataFilePath << "\n";
        return;
    }
    for (const auto& [id, book] : books)
        file << book.serialize() << "\n";
}

int Library::generateId() {
    return nextId++;
}

// Public: addBook

void Library::addBook(const std::string& title, const std::string& author) {
    int id = generateId();
    books.emplace(id, Book(id, title, author));

    printDivider();
    std::cout << "  Book added successfully!\n";
    std::cout << "  Assigned ID : " << id << "\n";
    std::cout << "  Title       : " << title  << "\n";
    std::cout << "  Author      : " << author << "\n";
    printDivider();
}

// Public: listBooks

void Library::listBooks() const {
    printDivider('=');
    std::cout << "  LIBRARY CATALOG  (" << totalBooks() << " book"
              << (totalBooks() != 1 ? "s" : "") << " | "
              << borrowedCount() << " borrowed)\n";
    printDivider('=');

    if (books.empty()) {
        std::cout << "  No books in the library yet.\n";
        printDivider('=');
        return;
    }

    for (const auto& [id, book] : books) {
        book.display();
        printDivider();
    }
}

// Public: borrowBook

bool Library::borrowBook(int id) {
    auto it = books.find(id);
    if (it == books.end()) {
        std::cout << "  [Error] No book found with ID " << id << ".\n";
        return false;
    }
    if (it->second.isBorrowed()) {
        std::cout << "  [Notice] \"" << it->second.getTitle()
                  << "\" is already borrowed.\n";
        return false;
    }
    it->second.setBorrowed(true);
    std::cout << "  You have borrowed: \"" << it->second.getTitle() << "\"\n";
    return true;
}

// Public: returnBook

bool Library::returnBook(int id) {
    auto it = books.find(id);
    if (it == books.end()) {
        std::cout << "  [Error] No book found with ID " << id << ".\n";
        return false;
    }
    if (!it->second.isBorrowed()) {
        std::cout << "  [Notice] \"" << it->second.getTitle()
                  << "\" was not borrowed.\n";
        return false;
    }
    it->second.setBorrowed(false);
    std::cout << "  Thank you for returning: \"" << it->second.getTitle() << "\"\n";
    return true;
}

// Public: searchBookByTitle

void Library::searchBookByTitle(const std::string& query) const {
    // Case-insensitive search
    std::string lowerQuery = query;
    std::transform(lowerQuery.begin(), lowerQuery.end(),
                   lowerQuery.begin(), ::tolower);

    std::vector<const Book*> results;
    for (const auto& [id, book] : books) {
        std::string lowerTitle = book.getTitle();
        std::transform(lowerTitle.begin(), lowerTitle.end(),
                       lowerTitle.begin(), ::tolower);
        if (lowerTitle.find(lowerQuery) != std::string::npos)
            results.push_back(&book);
    }

    printDivider('=');
    std::cout << "  Search results for \"" << query << "\": "
              << results.size() << " found\n";
    printDivider('=');

    if (results.empty()) {
        std::cout << "  No books matched your search.\n";
    } else {
        for (const auto* b : results) {
            b->display();
            printDivider();
        }
    }
}

// Public: utility

bool        Library::isEmpty()       const { return books.empty(); }
std::size_t Library::totalBooks()    const { return books.size(); }

std::size_t Library::borrowedCount() const {
    std::size_t count = 0;
    for (const auto& [id, book] : books)
        if (book.isBorrowed()) ++count;
    return count;
}
