//
// Created by MattFor on 17.03.2025.
//

#ifndef LIBRARY_H
#define LIBRARY_H

#include <string>
#include <iostream>

#include "Book.h"
#include "Member.h"

class Library
{
    static constexpr int MAX_BOOKS = 32;
    Book* books[MAX_BOOKS];

public:
    Library();
    ~Library();

    void addBook(Book* b);
    void removeBook(const std::string& isbn);

    void borrowBook(Member& m, const std::string& isbn);
    void returnBook(Member& m, const std::string& isbn);

    void displayBooks() const;
};

#endif // LIBRARY_H

// Zakomentować górę, by dostać implementację vectorową
#ifndef LIBRARY_H
#define LIBRARY_H

#include <vector>
#include <string>
#include <iostream>

#include "Book.h"
#include "Member.h"

class Library
{
    std::vector<Book> books;

public:
    Library();
    ~Library();

    void addBook(const Book &b);

    void removeBook(const std::string &isbn);

    void borrowBook(Member &m, const std::string &isbn);

    void returnBook(Member &m, const std::string &isbn);

    void displayBooks() const;
};

#endif // LIBRARY_H
