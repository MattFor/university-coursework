//
// Created by MattFor on 17.03.2025.
//

#include "Book.h"

Book::Book(const std::string& title, const std::string& author, const std::string& isbn)
    : title(title), author(author), isbn(isbn), available(true) {}

Book::~Book()
{
    std::cout << "destroying book" << '\n';
}

std::string Book::getTitle() const
{
    return title;
}

std::string Book::getAuthor() const
{
    return author;
}

std::string Book::getIsbn() const
{
    return isbn;
}

bool Book::isAvailable() const
{
    return available;
}

void Book::setTitle(const std::string& title)
{
    this->title = title;
}

void Book::setAuthor(const std::string& author)
{
    this->author = author;
}

void Book::setIsbn(const std::string& isbn)
{
    this->isbn = isbn;
}

void Book::setAvailable(bool avail)
{
    available = avail;
}

void Book::getInfo() const
{
    std::cout << "Title: " << title << ", Author: " << author << ", ISBN: " << isbn << ", Available: " << (available ? "yes" : "no") << '\n';
}
