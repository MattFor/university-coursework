#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <tgmath.h>

double f_scisle(double x)
{
    return pow(1.0 - x, 1.0/3.0);
}

double f_szereg(double x, const long double epsilon, const unsigned long long M, int *uzytek, int *precyzja_osiagnieta)
{
    long double wyraz = 0.0;
    long double wynik = 1.0;

    for (int n = 1; n < M; n++)
    {
        long double licznik = 1.0;
        long double mianownik = 1.0;

        for (int k = 1; k <= n; ++k)
        {
            licznik *= fabs(3 * (k - 1) - 1);
        }

        for (int k = 1; k <= n; ++k)
        {
            mianownik *= (3 * k);
        }

        *uzytek += 1;

        wyraz = (licznik / mianownik) * pow(x, n);
        wynik -= wyraz;

        if (fabs(wyraz) < epsilon)
        {
            *precyzja_osiagnieta = 1;

            if (n + 1 >= M)
            {
                *precyzja_osiagnieta = 2;
            }

            break;
        }
    }

    return wynik;
}

int main()
{
    double a,b,n;
    const long double epsilon = 0.0000000000001;
    const unsigned long long M = 40;

    printf("Wypisz zakres od a do b, liczby podaj oddzielone znakiem ENTER.\nNastepnie podaj czestotliwosc pomiaru, rowniez oddzielona znakiem ENTER\n");
    scanf("%lf%lf%lf", &a, &b, &n);

    if (n < 2 || n > 10000)
    {
        printf("Minimalna liczba podzialow to 2, a maksymalna to 10000!\n");
        exit(1);
    }

    if (b < a)
    {
        printf("Koniec przedzialu nie moze byc mniejszy od poczatku!\n");
        exit(1);
    }

    if (a == 1.0)
    {
        printf("Wartosc a (1) to maksymalna wartosc dziedziny funkcji, wiec nie mozna kontynuowac z operacja.\n");
        exit(1);
    }

    if (fabs(a) > 1.0 || fabs(b) > 1.0)
    {
        printf("Blad: wartosci 'a' i 'b' musza nalezec do przedzialu [-1, 1].\n");
        exit(1);
    }

    FILE *plik = fopen("../results.txt", "w");
    if (plik == NULL)
    {
        printf("Blad otwierania pliku!\n");
        exit(1);
    }

    double dx = (b - a) / n;

    printf("x\t\tf_szereg(x)\tf_scisle(x)\tliczba wyrazow\twarunek stopu\n");
    fprintf(plik, "x\t\tf_szereg(x)\tf_scisle(x)\tliczba wyrazow\twarunek stopu\n");

    for (int i = 0; i <= n; i++)
    {
        int uzytek = 1; // ilosc powtorzen
        int precyzja_zdobyta = 0;

        double x = a + i * dx;

        double y_fscisla = f_scisle(x);
        double y_fszereg = f_szereg(x, epsilon, M, &uzytek, &precyzja_zdobyta);

        char warunek_stop[17] = "precyzja\0";

        switch (precyzja_zdobyta)
        {
        case 0:
            strcpy(warunek_stop, "limit\0");
            break;
        case 1:
            strcpy(warunek_stop, "precyzja\0");
            break;
        case 2:
            strcpy(warunek_stop, "precyzja/limit\0");
            break;
        }

        printf("%10.4lf\t%5.8lf\t%5.8lf\t%d\t\t%s\n", x, y_fszereg, y_fscisla, uzytek, warunek_stop);
        fprintf(plik, "%10.4lf\t%10.4lf\t%10.4lf\t%d\t\t%s\n", x, y_fszereg, y_fscisla, uzytek, warunek_stop);
    }

    fclose(plik);

    return 0;
}
