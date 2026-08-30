//
// Created by MattFor on 17.03.2025.
//

#include "Library.h"

Library::Library()
{
    for (int i = 0; i < MAX_BOOKS; i++)
    {
        books[i] = nullptr;
    }
};

Library::~Library()
{
    for (int i = 0; i < MAX_BOOKS; i++)
    {
        if (books[i] != nullptr)
        {
            delete books[i];
            books[i] = nullptr;
        }
    }
};

void Library::addBook(Book* b)
{
    for (int i = 0; i < MAX_BOOKS; i++)
    {
        if (books[i] == nullptr)
        {
            books[i] = b;
            std::cout << "Added book: " << b->getTitle() << '\n';
            return;
        }
    }

    std::cout << "Out of free places to add a book." << '\n';
};

void Library::removeBook(const std::string& isbn)
{
    for (int i = 0; i < MAX_BOOKS; i++)
    {
        if (books[i] != nullptr && books[i]->getIsbn() == isbn)
        {
            std::cout << "Removing book: " << books[i]->getTitle() << '\n';
            delete books[i];
            books[i] = nullptr;
            return;
        }
    }

    std::cout << "Book with ISBN not found: " << isbn << '\n';
};

void Library::borrowBook(Member& m, const std::string& isbn)
{
    for (int i = 0; i < MAX_BOOKS; i++)
    {
        if (books[i] != nullptr && books[i]->getIsbn() == isbn)
        {
            if (books[i]->isAvailable())
            {
                books[i]->setAvailable(false);
                m.borrowBook();
                std::cout << "Book \"" << books[i]->getTitle() << "\" has been borrowed out by " << m.getName() << '\n';
            }
            else
            {
                std::cout << "Book is unavailable." << '\n';
            }

            return;
        }
    }

    std::cout << "Book with ISBN not found: " << isbn << '\n';
};

void Library::returnBook(Member& m, const std::string& isbn)
{
    for (int i = 0; i < MAX_BOOKS; i++)
    {
        if (books[i] != nullptr && books[i]->getIsbn() == isbn)
        {
            if (!books[i]->isAvailable())
            {
                books[i]->setAvailable(true);
                m.returnBook();
                std::cout << "Book \"" << books[i]->getTitle() << "\" has been returned by " << m.getName() << '\n';
            }
            else
            {
                std::cout << "Book has not been borrowed." << '\n';
            }

            return;
        }
    }

    std::cout << "Book with ISBN not found: " << isbn << '\n';
};

void Library::displayBooks() const
{
    std::cout << "List of books present in the library:" << '\n';

    for (int i = 0; i < MAX_BOOKS; i++)
    {
        if (books[i] != nullptr)
        {
            books[i]->getInfo();
        }
    }
};

/* Odkomentować do implementacji wektorowej.
#include <algorithm> 
#include "Library.h"

Library::Library() {};
Library::~Library() {};

void Library::addBook(const Book &b) 
{
    books.push_back(b);
    std::cout << "Added book: " << b.getTitle() << '\n';
};

void Library::removeBook(const std::string &isbn) 
{
    auto it = std::remove_if(books.begin(), books.end(), [&isbn](const Book &b) { return b.getIsbn() == isbn; });
    
    if (it != books.end()) 
    {
        std::cout << "Removing book with ISBN: " << isbn << '\n';
        books.erase(it, books.end());
    } 
    else 
    {
        std::cout << "Book with ISBN not found: " << isbn << '\n';
    }
};

void Library::borrowBook(Member &m, const std::string &isbn)
{
    for (auto &b : books)
    {
        if (b.getIsbn() == isbn)
        {
            if (b.isAvailable())
            {
                b.setAvailable(false);
                m.borrowBook();
                std::cout << "Book \"" << b.getTitle() << "\" has been borrowed by " << m.getName() << '\n';
            }
            else
            {
                std::cout << "Book is unavailable." << '\n';
            }

            return;
        }
    }

    std::cout << "Book with ISBN not found: " << isbn << '\n';
};

void Library::returnBook(Member &m, const std::string &isbn)
{
    for (auto &b : books)
    {
        if (b.getIsbn() == isbn)
        {
            if (!b.isAvailable())
            {
                b.setAvailable(true);
                m.returnBook();
                std::cout << "Book \"" << b.getTitle() << "\" has been borrowed by " << m.getName() << '\n';
            }
            else

                std::cout << "Book has not been borrowed." << '\n';
            }

            return;
        }
    }

    std::cout << "Book with ISBN not found: " << isbn << '\n';
};

void Library::displayBooks() const
{
    std::cout << "List of books in the library:" << '\n';

    for (const auto &b : books)
    {
        b.getInfo();
    }
};
*/
