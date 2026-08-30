//
// Created by MattFor on 18.03.2025.
//

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "calki.c"

double f1(double x)
{
    return -3.13*x*x*x + 14.5*x*x - 6*x + 7;
}

double f2(double x)
{
    const double y = cos(2 * x * x) / 2 * sin(8 * x * x) - 3 * cos(5 + x) + 1;
    return y;
}

int main(int argc, char *argv[])
{
    printf("od=");
    scanf("%lf",&c_od);
    printf("do=");
    scanf("%lf",&c_do);
    printf ("\n\nFunkcja 1 \n");
    printf( "wynik prostokaty - %lf\n" ,prostokaty(f1));
    printf( "wynik trapezy    - %lf\n" ,trapezy(f1));
    printf( "wynik MC   - %lf\n", mc(f1));
    printf("\n\nFunkcja 2 \n");
    printf( "wynik prostokaty - %lf\n" ,prostokaty(f2));
    printf( "wynik trapezy    - %lf\n" ,trapezy(f2));
    printf("wynik MC   - %lf\n", mc(f2));
    printf ("\n\nFunkcja 3 \n");
    printf( "wynik prostokaty - %lf\n" ,prostokaty(f3));
    printf( "wynik trapezy    - %lf\n" ,trapezy(f3));
    printf( "wynik MC   - %lf\n", mc(f3));
    printf("\n\nFunkcja 4 \n");
    printf( "wynik prostokaty - %lf\n" ,prostokaty(f4));
    printf( "wynik trapezy    - %lf\n" ,trapezy(f4));
    printf( "wynik MC   - %lf\n", mc(f4));

    return 0;
}