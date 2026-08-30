//
// Created by MattFor on 02.04.2025.
//

#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <iostream>

class Product
{
    int id;
    double price;
    std::string name;

public:
    Product();
    Product(int id, std::string name, double price);

    [[nodiscard]] int getId() const;
    [[nodiscard]] std::string getName() const;
    [[nodiscard]] double getPrice() const;

    void setId(int id);
    void setName(const std::string &name);
    void setPrice(double price);

    void writeToStream(std::ostream &out) const;
    void readFromStream(std::istream &in);

    void display() const;
};

#endif // PRODUCT_H

