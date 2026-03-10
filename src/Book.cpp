#include "../include/Book.h"
#include <sstream>
#include <iomanip>
#include <vector>
#include <stdexcept>

// Constructors

Book::Book()
    : id(0), title(""), author(""), borrowed(false) {}

Book::Book(int id, const std::string& title, const std::string& author)
    : id(id), title(title), author(author), borrowed(false) {}

// Getters

int                Book::getId()      const { return id; }
const std::string& Book::getTitle()   const { return title; }
const std::string& Book::getAuthor()  const { return author; }
bool               Book::isBorrowed() const { return borrowed; }

// Setters

void Book::setTitle(const std::string& t)  { title  = t; }
void Book::setAuthor(const std::string& a) { author = a; }
void Book::setBorrowed(bool status)        { borrowed = status; }

// Display

void Book::display() const {
    std::string status = borrowed ? "[ BORROWED ]" : "[ Available ]";
    std::cout << "  ID     : " << id           << "\n"
              << "  Title  : " << title         << "\n"
              << "  Author : " << author        << "\n"
              << "  Status : " << status        << "\n";
}

// Serialization  (format: id|title|author|borrowed)

std::string Book::serialize() const {
    return std::to_string(id)    + "|" +
           title                  + "|" +
           author                 + "|" +
           (borrowed ? "1" : "0");
}

Book Book::deserialize(const std::string& line) {
    std::istringstream ss(line);
    std::string token;
    std::vector<std::string> parts;

    while (std::getline(ss, token, '|'))
        parts.push_back(token);

    if (parts.size() != 4)
        throw std::runtime_error("Malformed book record: " + line);

    Book b(std::stoi(parts[0]), parts[1], parts[2]);
    b.setBorrowed(parts[3] == "1");
    return b;
}
