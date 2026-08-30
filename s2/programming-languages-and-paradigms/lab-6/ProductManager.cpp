//
// Created by MattFor on 02.04.2025.
//

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>

#include "ProductManager.h"

void ProductManager::addProduct(const Product &product)
{
    for (const auto &p : this->products)
    {
        if (p.getId() == product.getId())
        {
            throw std::runtime_error("Produkt o podanym ID już istnieje.");
        }
    }

    this->products.push_back(product);
}

void ProductManager::removeProduct(int id)
{
    const auto it = std::ranges::find_if(this->products, [id](const Product &p) {
        return p.getId() == id;
    });

    if (it != this->products.end())
    {
        this->products.erase(it);
    }
    else
    {
        throw std::runtime_error("Nie znaleziono produktu o podanym ID.");
    }
}

void ProductManager::displayProducts() const
{
    if (this->products.empty())
    {
        std::cout << "Brak produktów do wyświetlenia." << '\n';
        return;
    }

    for (const auto &p : this->products)
    {
        p.display();
        std::cout << "------------------------" << '\n';
    }
}

void ProductManager::saveToFile(const std::string &filename) const
{
    std::ofstream out(filename, std::ios::binary);

    if (!out)
    {
        throw std::runtime_error("Nie można otworzyć pliku do zapisu.");
    }

    // Zapis liczby produktów
    const size_t count = this->products.size();
    out.write(reinterpret_cast<const char*>(&count), sizeof(count));

    for (const auto &p : this->products)
    {
        p.writeToStream(out);
    }

    out.close();
}

void ProductManager::loadFromFile(const std::string &filename)
{
    std::ifstream in(filename, std::ios::binary);

    if (!in)
    {
        throw std::runtime_error("Nie można otworzyć pliku do odczytu.");
    }

    size_t count;
    this->products.clear();
    in.read(reinterpret_cast<char*>(&count), sizeof(count));

    for (size_t i = 0; i < count; ++i)
    {
        Product p;
        p.readFromStream(in);
        this->products.push_back(p);
    }

    in.close();
}
