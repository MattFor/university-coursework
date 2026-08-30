#include <stdio.h>
#define PI 3.14159265358979323846

void kolo(double r, double *w1, double *w2)
{
	*w1 = PI * r * r;
	*w2 = 2 * PI * r;
}

void zad9()
{
	double r, pole, obwod;
	printf("Podaj promien: ");
	scanf("%lf", &r);

	kolo(r, &pole, &obwod);

	printf("Pole: %.2lf\n", pole);
	printf("Obwod: %.2lf\n", obwod);
}

void zamien(int *x, int *y)
{
	int temp = *x;
	*x = *y;
	*y = temp;
}

void zad10()
{
	int a, b;
	printf("Podaj dwie liczby calkowite: ");
	scanf("%d %d", &a, &b);

	printf("Przed zamiana: a = %d, b = %d\n", a, b);
	zamien(&a, &b);
	printf("Po zamianie: a = %d, b = %d\n", a, b);
}

void oblicz_z(double x, double y, double *z, int *wzor)
{
	if ((x * x + y * y) <= 1)
	{
		*z = x * x + y;
		*wzor = 1;
	}
	else if (y > x + 5)
	{
		*z = 2 * x + y * y;
		*wzor = 2;
	}
	else if (x * x + y * y > 1 && y <= x + 5)
	{
		*z = 0.5 * (x * x) + y;
		*wzor = 3;
	}
	else
	{
		printf("ERROR - operacja nie wspierana przez funkcje.\n");
	}
}

void zad11()
{
	double x, y, z;
	int wzor;

	printf("Podaj x i y: ");
	scanf("%lf %lf", &x, &y);

	oblicz_z(x, y, &z, &wzor);

	printf("Wynik: z = %.2lf, wzor = %d\n", z, wzor);
}

int suma(int n)
{
	if (n == 0)
	{
		return 0;
	}

	return n + suma(n - 1);
}

void zad12()
{
	int n;
	printf("Podaj liczbe n: ");
	scanf("%d", &n);

	printf("Suma %d kolejnych liczb naturalnych wynosi: %d\n", n, suma(n));
}

void hanoi(int N, char A, char B, char C)
{
	if (N == 1)
	{
		printf("Przenies krazek z %c do %c\n", A, B);
	}
	else
	{
		hanoi(N - 1, A, C, B);
		printf("Przenies krazek z %c do %c\n", A, B);
		hanoi(N - 1, C, B, A);
	}
}

void zad13()
{
	int N = 4;
	printf("Rozwiazanie dla %d krazkow:\n", N);
	hanoi(N, 'A', 'B', 'C');
}

int main() {
	zad9();
	zad10();
	zad11();
	zad12();
	zad13();
}
