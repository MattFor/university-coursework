#include <array>
#include <iostream>

#include "Polynomial.h"

int main()
{
    // Definiujemy dwa wielomiany stopnia 2.
    // Wielomian: a0 + a1*x + a2*x^2
    std::array coeffs1 = { 1.0, -3.0, 2.0 };  // 1 - 3x + 2x^2
    std::array coeffs2 = { 0.0, 2.0, 1.0  };   // 0 + 2x + 1x^2

    const Polynomial<2> poly1(coeffs1);
    const Polynomial<2> poly2(coeffs2);

    std::cout << "Wielomian 1: ";
    printPolynomial(poly1);

    std::cout << "Wielomian 2: ";
    printPolynomial(poly2);

    // Dodawanie wielomianów
    const auto polySum = poly1 + poly2;
    std::cout << "Suma: ";
    printPolynomial(polySum);

    // Odejmowanie wielomianów
    const auto polyDiff = poly1 - poly2;
    std::cout << "Różnica: ";
    printPolynomial(polyDiff);

    // Mnożenie przez stałą
    const auto polyMult = poly1 * 2.0;
    std::cout << "Mnożenie przez 2: ";
    printPolynomial(polyMult);

    // Obliczanie wartości wielomianu dla x = 2
    constexpr double x = 2.0;
    std::cout << "Wartość wielomianu 1 dla x = " << x << ": " << poly1.evaluate(x) << '\n';

    return 0;
}
