#include <math.h>
#include <stdio.h>


void zad8()
{
    int k = 2;
    int m = 4;
    double x = 3.14;
    double y = 12.56;
    double z = 7.0;

    double w1 = pow(x / (y * z), 1./3) * log(x * x + y * y);
    double w2 = sin(k * (x / 2)) * cos(m * y) + y * exp(2 * x - 1);
    double w3 = fabs(x / (2 * pow(y, 2) + 1)) + sqrt(y / (pow(z, 2) + 3)) + 5 * pow(y + z, 3);
    double w4 = (x / (y * z)) * pow(z + 1, 1./3) + pow(pow(x, 2) + pow(z, 2) + 1, 1./k)-fabs(y);
    double w5 = 1 / (sqrt(pow(x, 2) + pow(y, 2) + pow(k, 2)) + 1/x * sin(k * y));

    printf("w1 = %.8lf\n", w1);
    printf("w2 = %.8lf\n", w2);
    printf("w3 = %.8lf\n", w3);
    printf("w4 = %.8lf\n", w4);
    printf("w5 = %.8lf\n", w5);
}

void zad9()
{
	double a = 0.0, b = 0.0, c = 0.0;
	int ret = -1;

	// Wprowadzenie danych
	printf("Program obliczenia rzeczywistych pierwiastkow rownania kwadratowego\n");
	printf("-------------------- a*x^2+b*x+c = 0 ------------------------------\n\n");
	printf("Podaj a, b, c: ");
	ret = scanf("%le %le %le", &a, &b, &c);

	if (ret != 3)
	{
		printf("Blad przy wczytaniu\n");
		printf("Wczytane: a = %e b = %e c = %e\n", a, b, c);
		return;
	}

	// Sprawdzenie, czy a != 0 (czyli czy jest to równanie kwadratowe)
	if (a == 0.0)
	{
		printf("To nie jest rownanie kwadratowe: a = 0.\n");
		return;
	}

	// Obliczenie delty
	double D = b * b - 4.0 * a * c;

	// Sprawdzenie wartości delty
	if (D < 0.0)
	{
		// Delta < 0, obliczamy pierwiastki zespolone
		double r1 = -b / (2.0 * a);  // część rzeczywista obu pierwiastków
		double u1 = sqrt(fabs(pow(b / (2.0 * a), 2.0) - (c / a))); // część urojona

		printf("Rownanie kwadratowe: %lf * X^2 + %lf * X + %lf = 0\n\n", a, b, c);
		printf("Pierwiastki zespolone:\n");
		printf("x1 = %lf + %lf i\n", r1, u1);
		printf("x2 = %lf - %lf i\n", r1, u1);
	}
	else
	{
		// Delta >= 0, obliczamy pierwiastki rzeczywiste
		double p1, p2, x1, x2;
		p1 = -b / (2.0 * a);
		p2 = sqrt(D) / (2.0 * a);
		x1 = p1 + p2;
		x2 = p1 - p2;

		printf("Rownanie kwadratowe: %lf * X^2 + %lf * X + %lf = 0\n\n", a, b, c);
		if (D == 0.0)
		{
			printf("Rownanie ma jeden pierwiastek rzeczywisty: x = %e\n", x1);
		}
		else
		{
			printf("Pierwiastki rzeczywiste: x1 = %e, x2 = %e\n", x1, x2);
		}
	}

	printf("---------------------------------------------------------\n");
}

void zad10()
{
    double a, b, c;

    printf("Wprowadz dlugosci bokow trojkata (a, b, c) oddzielone spacja:\n");
    scanf("%lf %lf %lf", &a, &b, &c);

    if (a + b > c && a + c > b && b + c > a)
    {
        double p = (a + b + c) / 2.0;
        double S = sqrt(p * (p - a) * (p - b) * (p - c));
        double R = S / p;

        printf("Pole trojkata: S = %.10lf\n", S);
        printf("Promien kola wpisanego: R = %.10lf\n", R);
    }
    else
    {
        printf("Podane dlugosci nie moga utworzyc trojkata.\n");
    }
}

void zad11()
{
    int a, b, c, d;

    printf("Wprowadz cztery liczby calkowite (a, b, c, d) oddzielone spacja:\n");
    scanf("%d %d %d %d", &a, &b, &c, &d);

    int max = a;
    int pozycja = 1;

    if (b > max)
    {
        max = b;
        pozycja = 2;
    }

    if (c > max)
    {
        max = c;
        pozycja = 3;
    }
    
    if (d > max)
    {
        max = d;
        pozycja = 4;
    }

    printf("Najwieksza liczba: %d\n", max);
    printf("Pozycja: %d\n", pozycja);
}

// Sekcja Zad 12
void trojkat(double a, double b, double c)
{
	if (a <= 0 || b <= 0 || c <= 0)
	{
		printf("Boki trojkata musza byc dodatnie.\n");
		return;
	}

	if (a + b > c && a + c > b && b + c > a)
	{
		double p = (a + b + c) / 2;  // Wzór Herona
		double pole = sqrt(p * (p - a) * (p - b) * (p - c));
		double obwod = a + b + c;
		printf("Trojkat - Pole: %.2lf, Obwod: %.2lf\n", pole, obwod);
	}
	else
	{
		printf("Podane boki nie spelniaja warunku trojkata.\n");
	}
}

void kwadrat(double a)
{
	if (a <= 0)
	{
		printf("Bok kwadratu musi byc dodatni.\n");
		return;
	}

	double pole = a * a;
	double obwod = 4 * a;
	printf("Kwadrat - Pole: %.2lf, Obwod: %.2lf\n", pole, obwod);
}

void prostokat(double a, double b)
{
	if (a <= 0 || b <= 0)
	{
		printf("Boki prostokata musza byc dodatnie.\n");
		return;
	}

	double pole = a * b;
	double obwod = 2 * (a + b);
	printf("Prostokat - Pole: %.2lf, Obwod: %.2lf\n", pole, obwod);
}

void kolo(double r)
{
	if (r <= 0)
	{
		printf("Promien kola musi byc dodatni.\n");
		return;
	}

	double pole = M_PI * r * r;
	double obwod = 2 * M_PI * r;
	printf("Kolo - Pole: %.2lf, Obwod: %.2lf\n", pole, obwod);
}

void zad12()
{
	double a, b, c, r;
	int wybor;

	printf("Wybierz figure:\n");
	printf("1 - Trojkat\n");
	printf("2 - Kwadrat\n");
	printf("3 - Prostokat\n");
	printf("4 - Kolo\n");
	printf("Wybierz opcje: ");
	scanf("%d", &wybor);

	switch (wybor) {
		case 1:
		{
			printf("Podaj dlugosci bokow trojkata (a, b, c): ");
			scanf("%lf %lf %lf", &a, &b, &c);
			trojkat(a, b, c);
		}
		break;
		case 2:
		{
			printf("Podaj dlugosc boku kwadratu (a): ");
			scanf("%lf", &a);
			kwadrat(a);
		}
		break;
		case 3:
		{
			printf("Podaj dlugosci bokow prostokata (a, b): ");
			scanf("%lf %lf", &a, &b);
			prostokat(a, b);
		}
		break;
		case 4:
		{
			printf("Podaj promien kola (r): ");
			scanf("%lf", &r);
			kolo(r);
		}
		break;
		default:
		{
			printf("Nieprawidlowy wybor.\n");
		}
	}
}

int main()
{
	zad8();
	zad10();
    zad11();
	zad12();
}
