#include <iostream>

#include "Order.h"

int main()
{
    Order order;
    const Book book1{"Title1", "Author1", 100};
    const Book book2{"Title2", "Author2", 200};

    order += book1;
    order += book2;

    order.show_order();

    const Book book3{"Title3", "Author3", 300};

    std::cout << '\n';

    order += book3;

    order.show_order();

    std::cout << "Base total price: " << order.calculate_total_price() << " | With 400 delivery: " << order.calculate_total_price(400) << '\n';
}