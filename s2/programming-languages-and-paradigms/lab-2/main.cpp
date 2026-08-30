//
// Created by MattFor on 17.03.2025.
//

#include <iostream>

#include "Library.h"
#include "Book.h"
#include "Member.h"

int main()
{
    Library lib;

    int liczbaKsiazek = 0;
    std::cout << "Ile książek chcesz dodać? ";
    std::cin >> liczbaKsiazek;
    std::cin.ignore();

    for (int i = 0; i < liczbaKsiazek; i++)
    {
        std::string title, author, isbn;
        std::cout << "Podaj tytuł książki: ";
        std::getline(std::cin, title);
        std::cout << "Podaj autora książki: ";
        std::getline(std::cin, author);
        std::cout << "Podaj ISBN książki: ";
        std::getline(std::cin, isbn);

        const auto b = new Book(title, author, isbn);
        lib.addBook(b);
    }

    int liczbaCzytelnikow = 0;
    std::cout << "Ile czytelników chcesz dodać? ";
    std::cin >> liczbaCzytelnikow;
    std::cin.ignore();

    auto** members = new Member*[liczbaCzytelnikow];
    for (int i = 0; i < liczbaCzytelnikow; i++)
    {
        std::string name;
        std::cout << "Podaj imię czytelnika: ";
        std::getline(std::cin, name);
        members[i] = new Member(name);
    }

    std::string isbnWypozyczenia;
    std::cout << "Podaj ISBN książki do wypożyczenia: ";
    std::getline(std::cin, isbnWypozyczenia);
    if (liczbaCzytelnikow > 0)
    {
        lib.borrowBook(*members[0], isbnWypozyczenia);
    }

    lib.displayBooks();

    std::string isbnZwrotu;
    std::cout << "Podaj ISBN książki do zwrotu: ";
    std::getline(std::cin, isbnZwrotu);

    if (liczbaCzytelnikow > 0)
    {
        lib.returnBook(*members[0], isbnZwrotu);
    }

    lib.displayBooks();

    for (int i = 0; i < liczbaCzytelnikow; i++)
    {
        delete members[i];
    }

    delete [] members;
}
