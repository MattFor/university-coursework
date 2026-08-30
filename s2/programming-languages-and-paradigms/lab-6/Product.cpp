//
// Created by MattFor on 02.04.2025.
//

#include <fstream>
#include <utility>

#include "Product.h"

Product::Product() : id(0), price(0.0) {}

Product::Product(const int id, std::string name, const double price) : id(id), price(price), name(std::move(name)) {}

int Product::getId() const
{
    return this->id;
}

std::string Product::getName() const
{
    return this->name;
}

double Product::getPrice() const
{
    return this->price;
}

void Product::setId(const int id)
{
    this->id = id;
}

void Product::setName(const std::string &name)
{
    this->name = name;
}

void Product::setPrice(const double price)
{
    this->price = price;
}

// Zapis do strumienia binarnego: najpierw ID, potem długość napisu, dane napisu oraz cenę
void Product::writeToStream(std::ostream &out) const
{
    out.write(reinterpret_cast<const char*>(&this->id), sizeof(this->id));
    const size_t nameLength = this->name.size();
    out.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
    out.write(this->name.c_str(), static_cast<long long>(nameLength));
    out.write(reinterpret_cast<const char*>(&this->price), sizeof(this->price));
}

// Odczyt ze strumienia binarnego
void Product::readFromStream(std::istream &in)
{
    size_t nameLength;
    in.read(reinterpret_cast<char*>(&this->id), sizeof(this->id));
    in.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));

    const auto buffer = new char[nameLength + 1];
    in.read(buffer, static_cast<long long>(nameLength));
    buffer[nameLength] = '\0';

    this->name = std::string(buffer);

    delete[] buffer;
    in.read(reinterpret_cast<char*>(&this->price), sizeof(this->price));
}

// Wyświetlanie informacji o produkcie z wykorzystaniem RTTI
void Product::display() const
{
    std::cout << "Typ obiektu: " << typeid(*this).name() << '\n';
    std::cout << "ID: " << this->id << '\n';
    std::cout << "Nazwa: " << this->name << '\n';
    std::cout << "Cena: " << this->price << '\n';
}
