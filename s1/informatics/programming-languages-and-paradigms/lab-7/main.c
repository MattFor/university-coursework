#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void zad6 ()
{
    printf("Popatrzeć do pliku answer.txt\n");
}

void inicjalizuj_tablice(int *tab, const int n)
{
    for (int i = 0; i < n; i++)
    {
        tab[i] = rand() % 100;
    }
}

void zad10 ()
{
    int n;

    printf("Podaj rozmiar tablicy: ");
    scanf("%d", &n);

    const auto t1 = (int *)malloc(n * sizeof(int));
    const auto t2 = (int *)malloc(n * sizeof(int));

    if (t1 == NULL || t2 == NULL)
    {
        printf("Błąd przydzielania pamięci.\n");
        return;
    }

    inicjalizuj_tablice(t1, n);

    int min = t1[0], max = t1[0];
    int min_pos = 0, max_pos = 0;

    for (int i = 1; i < n; i++)
    {
        if (t1[i] < min)
        {
            min = t1[i];
            min_pos = i;
        }

        if (t1[i] > max)
        {
            max = t1[i];
            max_pos = i;
        }
    }

    printf("Tablica t1: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", t1[i]);
    }
    printf("\n");

    printf("Minimum: %d, pozycja: %d\n", min, min_pos);
    printf("Maksimum: %d, pozycja: %d\n", max, max_pos);

    memcpy(t2, t1, n * sizeof(int));

    printf("Tablica t2: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", t2[i]);
    }
    printf("\n");

    free(t1);
    free(t2);
}

void zad14 ()
{
    printf("Reszta w tych innych plikach\n");
}

int main ()
{
    srand(time(nullptr));

    zad6();
    zad10();
    zad14();
}
