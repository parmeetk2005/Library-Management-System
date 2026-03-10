#pragma once

#include <string>
#include <iostream>

class Book {
private:
    int         id;
    std::string title;
    std::string author;
    bool        borrowed;

public:
    // Constructors
    Book();
    Book(int id, const std::string& title, const std::string& author);

    // Getters
    int                getId()       const;
    const std::string& getTitle()    const;
    const std::string& getAuthor()   const;
    bool               isBorrowed()  const;

    // Setters
    void setTitle(const std::string& title);
    void setAuthor(const std::string& author);
    void setBorrowed(bool status);

    // Display
    void display() const;

    // Serialization helpers (for file I/O)
    std::string serialize()   const;
    static Book deserialize(const std::string& line);
};
