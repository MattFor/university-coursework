//
// Created by MattFor on 17.03.2025.
//

#ifndef BOOK_H
#define BOOK_H

#include <string>
#include <iostream>

class Book
{
    std::string isbn;     // Numer ISBN max 10
    std::string title;    // Tytuł max 32
    std::string author;   // Autor max 32

    bool available;

public:
    Book(const std::string& title, const std::string& author, const std::string& isbn);

    ~Book();

    [[nodiscard]] bool isAvailable() const;
    [[nodiscard]] std::string getIsbn() const;
    [[nodiscard]] std::string getTitle() const;
    [[nodiscard]] std::string getAuthor() const;

    void setAvailable(bool avail);
    void setIsbn(const std::string& isbn);
    void setTitle(const std::string& title);
    void setAuthor(const std::string& author);

    void getInfo() const;
};

#endif // BOOK_H
