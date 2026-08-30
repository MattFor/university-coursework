#include <stdio.h>

int zad6(const int n)
{
    if (n <= 0)
    {
        return -1;
    }

    if (n == 1 || n == 2)
    {
        return 1;
    }
    
    return zad6(n - 1) + zad6(n - 2);
}

int zad7_(const int n, const int a, const int b)
{
    if (n == 0)
    {
        return a;
    }

    if (n == 1)
    {
        return b;
    }

    return zad7_(n - 1, b, a + b);
}

int zad7(const int n)
{
    return zad7_(n, 0, 1);
}

int zad8_recursive(const int x, const unsigned int n)
{
    if (n == 0) return 1;
    return x * zad8_recursive(x, n - 1);
}

int zad8_iterative(const int x, const unsigned int n)
{
    int result = 1;

    for (unsigned int i = 0; i < n; i++)
    {
        result *= x;
    }

    return result;
}

int zad9_(const int n, const int divisor)
{
    if (n < 2)
    {
        return 0;
    }

    if (divisor * divisor > n)
    {
        return 1;
    }

    if (n % divisor == 0)
    {
        return 0;
    }

    return zad9_(n, divisor + 1);
}

int zad9_recursive(const int n)
{
    return zad9_(n, 2);
}

int zad9_iterative(const int n)
{
    if (n < 2)
    {
        return 0;
    }

    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0) return 0;
    }

    return 1;
}

int f_const()
{
    return 1;
}

int zad10_F_recursive(const int a, const int b, int (*f)(int))
{
    if (a > b)
    {
        return 0;
    }

    return f(a) + zad10_F_recursive(a + 1, b, f);
}

int zad10_F_iterative(const int a, const int b, int (*f)(int))
{
    int sum = 0;

    for (int i = a; i <= b; i++)
    {
        sum += f(i);
    }

    return sum;
}

//  6, 7, 8, 9 i 10
int main()
{
    constexpr int n6 = 7;
    printf("Zadanie 6: %d-ty wyraz ciągu Fibonacciego (rekurencyjnie): %d\n", n6, zad6(n6));

    constexpr int n7 = 7;
    printf("Zadanie 7: %d-ty wyraz ciągu Fibonacciego (rekurencja ogonowa): %d\n", n7, zad7(n7));

    constexpr int base = 2;
    constexpr int exponent = 5;
    printf("Zadanie 8: %d^%d (rekurencyjnie): %d\n", base, exponent, zad8_recursive(base, exponent));
    printf("Zadanie 8: %d^%d (iteracyjnie): %d\n", base, exponent, zad8_iterative(base, exponent));

    constexpr int prime_check = 29;
    printf("Zadanie 9: Czy liczba %d jest pierwsza (rekurencyjnie)? %s\n", prime_check, zad9_recursive(prime_check) ? "Tak" : "Nie");
    printf("Zadanie 9: Czy liczba %d jest pierwsza (iteracyjnie)? %s\n", prime_check, zad9_iterative(prime_check) ? "Tak" : "Nie");

    constexpr int a = 2;
    constexpr int b = 5;
    printf("Zadanie 10: F(%d, %d, f_constant) (rekurencyjnie): %d\n", a, b, zad10_F_recursive(a, b, f_const));
    printf("Zadanie 10: F(%d, %d, f_constant) (iteracyjnie): %d\n", a, b, zad10_F_iterative(a, b, f_const));
}