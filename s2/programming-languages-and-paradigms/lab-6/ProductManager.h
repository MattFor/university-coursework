//
// Created by MattFor on 02.04.2025.
//

#ifndef PRODUCTMANAGER_H
#define PRODUCTMANAGER_H

#include <vector>
#include <string>

#include "Product.h"

class ProductManager
{
    std::vector<Product> products;

public:
    void addProduct(const Product &product);
    void removeProduct(int id);
    void displayProducts() const;
    void saveToFile(const std::string &filename) const;
    void loadFromFile(const std::string &filename);
};

#endif // PRODUCTMANAGER_H
