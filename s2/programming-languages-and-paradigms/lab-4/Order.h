//
// Created by MattFor on 19/03/2025.
//

#ifndef ORDER_H
#define ORDER_H

#include <string>
#include <vector>

struct Book
{
    int         price{};

    std::string title;
    std::string author;
    Book() = default;
    Book(const char* str, const char* text, int i)
    {
        this->title = str;
        this->author = text;
        this->price = i;
    };
};

class Order
{
    std::vector <Book> books = {};

public:
    Order() = default;

    void show_order();

    [[nodiscard]] int get_book_count() const;
    int calculate_total_price(int delivery = -1);

    Order& operator += (const Book& book);
};

#endif //ORDER_H
