#include <cmath>
#include <string>
#include <iostream>

void zad1()
{
    int i;

    printf("Podaj liczbę.\n");
    scanf(" %d", &i);

    if (i % 2 == 0)
    {
        printf("Liczba jest parzysta.\n");
    }
    else
    {
        printf("Liczba nie jest parzysta.\n");
    }
}

void zad2()
{
    int a, b, c;

    printf("Podaj liczbę 1.\n");
    scanf(" %d", &a);

    printf("Podaj inną liczbę 2.\n");
    scanf(" %d", &b);

    printf("Podaj inną liczbę 3.\n");
    scanf(" %d", &c);

    if (a > c) // A jest większe od C
    {
        if (a > b) // A jest największe
        {
            printf("%d jest największą liczbą. Jest to pierwsza podana liczba.\n", a);
            return;
        }

        // Zostaje B i C
        if (c > b)
        {
            printf("%d jest największą liczbą. Jest to ostatnia podana liczba.\n", c);
            return;
        }
        else if (c < b)
        {
            printf("%d jest największą liczbą. Jest to druga podana liczba.\n", b);
            return;
        }
    }
    else // C jest większe od A
    {
        if (c > b)
        {
            printf("%d jest największą liczbą. Jest to ostatnia podana liczba.\n", c);
            return;
        }

        // Zostaje A i B
        if (a > b) // A jest największe
        {
            printf("%d jest największą liczbą. Jest to pierwsza podana liczba.\n", a);
            return;
        }
        else if (a < b)
        {
            printf("%d jest największą liczbą. Jest to druga podana liczba.\n", b);
            return;
        }
    }

    if (b > a)
    {
        if (b > c)
        {
            printf("%d jest największą liczbą. Jest to druga podana liczba.\n", b);
        }

        if (c > b)
        {
            printf("%d jest największą liczbą. Jest to ostatnia podana liczba.\n", c);
        }
    }
    else
    {
        printf("%d jest największą liczbą. Jest to pierwsza podana liczba.\n", a);
    }
}

void zad3()
{
    int tablica[5] = {1, 2, 3, 4, 5};

    for (int i = 0; i < 5; i++)
    {
        printf("Podaj liczbę %d.\n", i + 1);
        scanf(" %d", &tablica[i]);
    }

    int c;
    int min = tablica[0];
    int max = tablica[0];
    for (int i = 0; i < 5; i++)
    {
        c = tablica[i];

        if (c < min)
        {
            min = c;
        }

        if (c > max)
        {
            max = c;
        }
    }

    printf("Największa liczba to %d.\n", max);
    printf("Najmniejsza liczba to %d.\n", min);

}

void zad4()
{
    int matrix[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

    int sum = 0;

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            printf("Podaj liczbę %d, %d\n", i + 1, j + 1);
            scanf(" %d", &matrix[i][j]);
        }
    }

    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            sum += matrix[i][j];
        }
    }

    printf("Suma liczb w tej macierzy to %d.\n", sum);
}

void zad5()
{
    int tablica[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

    for (int i = 0; i < 10; i++)
    {
        printf("Podaj liczbę %d.\n", i + 1);
        scanf(" %d", &tablica[i]);
    }

    int sum = 0.0;
    for (int i = 0; i < 10; i++)
    {
        sum += tablica[i];
    }

    printf("Średnia liczb w tej tablicy to: %f\n", sum/10.0);
}

void zad6()
{
    std::string liczba;

    printf("Podaj liczbę.\n");
    std::getline(std::cin, liczba);

    int suma = 0;

    for (int i = 0; i < liczba.length(); i++)
    {
        suma += liczba[i] - '0';
    }

    printf("Suma cyfr to %d.\n", suma);
}

void zad7()
{
    int liczba = 0;

    do
    {
        printf("Podaj liczbę większą od 10.");
        scanf(" %d", &liczba);
    } while (liczba <= 10);

    printf("Gratulacje! Umiesz liczyć do 20!\n");
}

void zad8()
{
    int a, b;

    printf("Podaj dodatnią długość A prostokąta.\n");
    scanf(" %d", &a);

    printf("Podaj dodatnią długość B prostokąta.\n");
    scanf(" %d", &b);

    for (int i = 0; i < b; i++)
    {
        for (int j = 0; j < a; j++)
        {
            if (i == 0 || i == a - 1 || j == 0 || j == b - 1)
            {
                printf("*");
            }
            else
            {
                printf(" ");
            }
        }

        printf("\n");
    }
}

int main()
{
    // zad1();
    zad2();
    zad3();
    zad4();
    zad5();
    zad6();
    zad7();
    zad8();
}
