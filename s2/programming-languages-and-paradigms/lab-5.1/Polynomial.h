#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <array>
#include <cmath>
#include <cstdlib>
#include <iostream>

template <int Degree, typename T = double>
class Polynomial
{
    std::array<T, Degree + 1> coeffs;

public:
    explicit Polynomial(const std::array<T, Degree + 1>& coefficients);
    Polynomial();

    Polynomial operator + (const Polynomial& other) const;
    Polynomial operator - (const Polynomial& other) const;
    Polynomial operator * (T constant) const;
    T evaluate(T x) const;

    const std::array<T, Degree + 1>& getCoefficients() const;
};

template <int Degree, typename T>
void printPolynomial(const Polynomial<Degree, T>& poly);

#include "Polynomial.cpp"

#endif // POLYNOMIAL_H
