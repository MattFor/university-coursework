//
// Created by MattFor on 19/03/2025.
//

#include "Order.h"

#include <iostream>

void Order::show_order()
{
    if (this->books.size() == 0)
    {
        std::cout << "There are no books." << '\n';
        return;
    }

    int i = 1;
    for (const auto& [price, title, author] : this->books)
    {
        std::cout << i++ << ". Title " << title << " Author: " << author << " Price: " << price << '\n';
    }
};

int Order::calculate_total_price(const int delivery)
{
    int sum = delivery == -1 ? 0 : delivery;

    for (const auto& book : this->books)
    {
        sum += book.price;
    }

    return sum;
};

int Order::get_book_count() const
{
    return this->books.size();
};

Order& Order::operator += (const Book& book)
{
    this->books.push_back(book);
    return *this;
};

