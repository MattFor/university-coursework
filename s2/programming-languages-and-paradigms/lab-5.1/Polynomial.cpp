#include "Polynomial.h"

template <int Degree, typename T>
Polynomial<Degree, T>::Polynomial(const std::array<T, Degree + 1>& coefficients) : coeffs(coefficients) {}

template <int Degree, typename T>
Polynomial<Degree, T>::Polynomial()
{
    coeffs.fill(0);
}

template <int Degree, typename T>
Polynomial<Degree, T> Polynomial<Degree, T>::operator+(const Polynomial<Degree, T>& other) const
{
    Polynomial result;
    for (int i = 0; i <= Degree; i++)
    {
        result.coeffs[i] = this->coeffs[i] + other.coeffs[i];
    }

    return result;
}

template <int Degree, typename T>
Polynomial<Degree, T> Polynomial<Degree, T>::operator-(const Polynomial<Degree, T>& other) const
{
    Polynomial result;

    for (int i = 0; i <= Degree; i++)
    {
        result.coeffs[i] = this->coeffs[i] - other.coeffs[i];
    }

    return result;
}

// Operator mnożenia wielomianu przez stałą
template <int Degree, typename T>
Polynomial<Degree, T> Polynomial<Degree, T>::operator*(T constant) const
{
    Polynomial result;
    for (int i = 0; i <= Degree; i++)
    {
        result.coeffs[i] = this->coeffs[i] * constant;
    }

    return result;
}

template <int Degree, typename T>
T Polynomial<Degree, T>::evaluate(T x) const
{
    T result = 0;
    for (int i = 0; i <= Degree; i++)
    {
        result += coeffs[i] * std::pow(x, i);
    }

    return result;
}

template <int Degree, typename T>
const std::array<T, Degree + 1>& Polynomial<Degree, T>::getCoefficients() const
{
    return coeffs;
}

template <int Degree, typename T>
void printPolynomial(const Polynomial<Degree, T>& poly)
{
    const auto& coeffs = poly.getCoefficients();

    bool firstTerm = true;
    for (int i = Degree; i >= 0; --i)
    {
        if (coeffs[i] != 0)
        {
            if (!firstTerm)
            {
                std::cout << (coeffs[i] > 0 ? " + " : " - ");
            }
            else
            {
                if (coeffs[i] < 0)
                {
                    std::cout << "-";
                }

                firstTerm = false;
            }

            std::cout << std::abs(coeffs[i]);
            if (i > 0)
            {
                std::cout << "x";

                if (i > 1)
                {
                    std::cout << "^" << i;
                }
            }
        }
    }

    if(firstTerm)
    {
        std::cout << "0";
    }

    std::cout << '\n';
}
