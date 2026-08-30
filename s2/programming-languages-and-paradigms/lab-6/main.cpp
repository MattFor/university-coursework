//
// Created by MattFor on 02.04.2025.
//


#include <iostream>
#include <exception>

#include "Product.h"
#include "ProductManager.h"

int main()
{
    try
    {
        ProductManager manager;

        // Dodawanie produktów
        const Product p1(1, "Produkt A", 10.5);
        const Product p2(2, "Produkt B", 20.0);
        manager.addProduct(p1);
        manager.addProduct(p2);

        // Wyświetlenie produktów przed zapisem do pliku
        std::cout << "Produkty przed zapisem do pliku:" << '\n';
        manager.displayProducts();

        // Zapis do pliku binarnego
        manager.saveToFile("produkty.dat");

        // Usunięcie produktu o ID 1
        manager.removeProduct(1);
        std::cout << "\nProdukty po usunięciu produktu o ID 1:" << '\n';
        manager.displayProducts();

        // Wczytanie produktów z pliku
        manager.loadFromFile("produkty.dat");
        std::cout << "\nProdukty po odczycie z pliku:" << '\n';
        manager.displayProducts();

    }
    catch (std::exception &ex)
    {
        std::cerr << "Błąd: " << ex.what() << '\n';
    }
}
