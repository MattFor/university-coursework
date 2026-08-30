//
// Created by MattFor on 18.03.2025.
//

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define lp 1000

static double c_od, c_do;

static double f3(double x)
{
    return 3*sin(0.5*x)*pow(cos(x),2.0) + 0.5;
}

static double f4(double x)
{
    return pow(x - 2.5, 3.0) - 3*x + 12;
}

static double prostokaty(double (*f)(double))
{
    double suma = 0.0;
    const double krok = (c_do - c_od) / lp;

    for (double p = c_od + krok / 2; p < c_do; p += krok)
    {
        suma += (*f)(p) * krok;
    }

    return suma;
}


static double trapezy(double (*f)(double))
{
    const double krok = (c_do - c_od) / lp;
    double suma = 0.0;
    double prev_f = f(c_od);

    for (int i = 1; i <= lp; i++)
    {
        const double x = c_od + i * krok;
        const double curr_f = f(x);
        suma += (prev_f + curr_f) * krok / 2;
        prev_f = curr_f;
    }

    return suma;
}


static double mc(double (*f)(double))
{
    const int N = lp * 10;
    double sum = 0.0;

    for (int i = 0; i < N; i++)
    {
        const double x = c_od + (c_do - c_od) * ((double)rand() / RAND_MAX);
        sum += f(x);
    }

    const double average = sum / N;
    return average * (c_do - c_od);
}
