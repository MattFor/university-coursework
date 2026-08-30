#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

double oblicz (const double x, double (*f)(double))
{
    return x * x + f(x);
}

double f_sin (const double x)
{
    return sin(x);
}

double f_cos (const double x)
{
    return cos(x);
}

#define MAX_ITER 100
#define EPS 1e-6

// Funkcja Newtona
int newton (double *x, int n, double eps, double(*f1)(double), double(*f2)(double))
{
    double x1;
    int i = 0;
    do {
        x1 = -(*f1)(*x) / (*f2)(*x);
        *x += x1;
        printf("Iteracja %d, x = %.6f\n", i, *x);
        if (fabs(x1) < eps)
        {
            return 0;
        }
    } while (i++ < n);
    return 1;
}

double f1 (const double x)
{
    return sin(x) - 0.5 * x;
}

double f1_pochodna(const double x)
{
    return cos(x) - 0.5;
}

double f2(const double x) {
    return tan(x) - 2 * x;
}


double f2_pochodna(const double x)
{
    return 1 / (cos(x) * cos(x)) - 2;
}

void zad4 ()
{
    constexpr double x = 1.0;

    double y_sin = oblicz(x, f_sin);
    printf("y dla f(x) = sin(x), x = %.2f: %.2f\n", x, y_sin);

    double y_cos = oblicz(x, f_cos);
    printf("y dla f(x) = cos(x), x = %.2f: %.2f\n", x, y_cos);

    double x0 = 0.5;
    constexpr int n = MAX_ITER;
    constexpr double eps = EPS;

    newton(&x0, n, eps, f1, f1_pochodna);
    printf("Rozwiązanie dla f(x) = sin(x) - 0.5x: x = %.6f\n", x0);

    x0 = 0.2;
    newton(&x0, n, eps, f2, f2_pochodna);
    printf("Rozwiązanie dla g(x) = tg(x) - 2x: x = %.6f\n", x0);
}

typedef struct CO
{
    double re;
    double im;
} COMPLEX;

COMPLEX pierwiastki_kwadratowe(double a, double b, double c)
{
    COMPLEX pierwiastek;
    const double delta = b * b - 4 * a * c;

    if (delta >= 0)
    {
        pierwiastek.re = (-b + sqrt(delta)) / (2 * a);
        pierwiastek.im = 0;
    }
    else
    {
        pierwiastek.re = -b / (2 * a);
        pierwiastek.im = sqrt(fabs(pow(b / (2 * a), 2) - c / a));
    }

    return pierwiastek;
}

COMPLEX dodaj_liczby_zespolone(const COMPLEX z1, const COMPLEX z2)
{
    COMPLEX suma;
    suma.re = z1.re + z2.re;
    suma.im = z1.im + z2.im;
    return suma;
}

void zad10 ()
{
    printf("funkcja znajduje sie w pliku main.c\n");
}

struct student
{
    char* imie;
    char* nazwisko;
    int rok;
    char* adres;
    double stypendium;
};

int porownaj_stypendium(const void* a, const void* b)
{
    double styp1 = ((struct student*)a)->stypendium;
    double styp2 = ((struct student*)b)->stypendium;

    if (styp1 < styp2)
    {
        return 1;
    }

    if (styp1 > styp2)
    {
        return -1;
    }

    return 0;
}

void zad11 ()
{
    int n;

    FILE* file = fopen("studenci.txt", "r");
    if (file == NULL)
    {
        printf("Nie mozna otworzyc pliku\n");
        return;
    }

    fscanf(file, "%d\n", &n);
    const auto studenci = (struct student*)malloc(n * sizeof(struct student));

    for (int i = 0; i < n; i++)
    {
        char buffer[256];

        fgets(buffer, sizeof(buffer), file);
        buffer[strcspn(buffer, "\n")] = '\0';
        studenci[i].imie = strdup(buffer);

        fgets(buffer, sizeof(buffer), file);
        buffer[strcspn(buffer, "\n")] = '\0';
        studenci[i].nazwisko = strdup(buffer);

        fgets(buffer, sizeof(buffer), file);
        studenci[i].rok = atoi(buffer);

        fgets(buffer, sizeof(buffer), file);
        buffer[strcspn(buffer, "\n")] = '\0';
        studenci[i].adres = strdup(buffer);

        fgets(buffer, sizeof(buffer), file);
        studenci[i].stypendium = atof(buffer);
    }

    struct student najwyzsze_stypendium = studenci[0];
    for (int i = 1; i < n; i++)
    {
        if (studenci[i].stypendium > najwyzsze_stypendium.stypendium)
        {
            najwyzsze_stypendium = studenci[i];
        }
    }
    printf("Student z najwyzszym stypendium: %s %s, stypendium: %.2f\n", najwyzsze_stypendium.imie, najwyzsze_stypendium.nazwisko, najwyzsze_stypendium.stypendium);

    qsort(studenci, n, sizeof(struct student), porownaj_stypendium);

    printf("\nStudenci posortowani po stypendium (malejaco):\n");
    for (int i = 0; i < n; i++)
    {
        printf("%s %s, %d, %s, stypendium: %.2f\n", studenci[i].imie, studenci[i].nazwisko, studenci[i].rok, studenci[i].adres, studenci[i].stypendium);
    }

    for (int i = 0; i < n; i++)
    {
        free(studenci[i].imie);
        free(studenci[i].nazwisko);
        free(studenci[i].adres);
    }

    fclose(file);
    free(studenci);
}


int main ()
{
	zad4();
	zad10();
	zad11();
}