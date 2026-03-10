#pragma once

#include "Book.h"
#include <map>
#include <string>
#include <vector>

class Library {
private:
    std::map<int, Book> books;
    int                 nextId;
    std::string         dataFilePath;

    // Private helpers
    void loadFromFile();
    void saveToFile()  const;
    int  generateId();

public:
    explicit Library(const std::string& filePath = "data/books.txt");
    ~Library();

    // Core operations
    void addBook(const std::string& title, const std::string& author);
    void listBooks()                          const;
    bool borrowBook(int id);
    bool returnBook(int id);
    void searchBookByTitle(const std::string& query) const;

    // Utility
    bool        isEmpty()        const;
    std::size_t totalBooks()     const;
    std::size_t borrowedCount()  const;
};
