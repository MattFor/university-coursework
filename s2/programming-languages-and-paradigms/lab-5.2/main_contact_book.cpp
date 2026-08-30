#include <string>
#include <vector>
#include <iostream>
#include <algorithm>

struct Contact
{
    std::string phone;
    std::string surname;
};

void addContact(std::vector<Contact>& addressBook, const std::string& surname, const std::string& phone)
{
    addressBook.push_back({surname, phone});
}

void displayContacts(const std::vector<Contact>& addressBook)
{
    std::cout << "Książka adresowa:" << '\n';
    for (const auto& [phone, surname] : addressBook) {
        std::cout << surname << " - " << phone << '\n';
    }
}

void sortContacts(std::vector<Contact>& addressBook)
{
    std::ranges::sort(addressBook, [](const Contact& a, const Contact& b) {
        return a.surname < b.surname;
    });
}

void searchContact(const std::vector<Contact>& addressBook, const std::string& surname)
{
    const auto it = std::ranges::find_if(addressBook, [&](const Contact& c) {
        return c.surname == surname;
    });

    if (it != addressBook.end())
    {
        std::cout << "Znaleziono: " << it->surname << " - " << it->phone << '\n';
    }
    else
    {
        std::cout << "Nie znaleziono kontaktu o nazwisku: " << surname << '\n';
    }
}

int main()
{
    std::vector<Contact> addressBook;

    addContact(addressBook, "Kowalski", "123456789");
    addContact(addressBook, "Nowak", "987654321");
    addContact(addressBook, "Wiśniewski", "555444333");
    addContact(addressBook, "Zieliński", "111222333");

    addContact(addressBook, "Wójcik", "222333444");

    sortContacts(addressBook);

    displayContacts(addressBook);

    std::cout << "\nWyszukiwanie kontaktu o nazwisku 'Nowak':" << '\n';
    searchContact(addressBook, "Nowak");
}
