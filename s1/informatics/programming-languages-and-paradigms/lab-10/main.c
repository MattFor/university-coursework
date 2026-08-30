#include <stdio.h>

void zad2 ()
{
	printf("zadanie 2 w oddzielnych plikach.\n");
}

struct liczba8 {
	__int8 a;
	__int8 b;
};

union liczba16 {
	struct liczba8 jeden;
	__int16 dwa;
};

void zad4 ()
{
	union liczba16 liczba;

	liczba.jeden.a = 200;
	liczba.jeden.b = 50;

	printf("Wartości struktury:\n");
	printf("a = %i, b = %i\n", liczba.jeden.a, liczba.jeden.b);

	printf("Wartość unii jako __int16:\n");
	printf("dwa = %i\n", liczba.dwa);

	printf("Wartości struktury (szesnastkowo):\n");
	printf("a = %x, b = %x\n", liczba.jeden.a, liczba.jeden.b);
	printf("Wartość unii jako __int16 (szesnastkowo):\n");
	printf("dwa = %x\n", liczba.dwa);
}

int main ()
{
	zad2();
	zad4();
}