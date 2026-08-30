#include <stdio.h>
#include <string.h>


int znajdz_pozycje_znaku(const char *tekst, char znak)
{
	for (int i = 0; tekst[i] != '\0'; i++)
	{
		if (tekst[i] == znak)
		{
			return i;
		}
	}

	return -1;
}

void usun_pierwsze_wystapienie(char *tekst, char znak)
{
	int pozycja = znajdz_pozycje_znaku(tekst, znak);

	if (pozycja != -1)
	{
		for (int i = pozycja; tekst[i] != '\0'; i++)
		{
			tekst[i] = tekst[i + 1];
		}
	}
}

void zamien_znak(char *tekst, char stary_znak, char nowy_znak)
{
	for (int i = 0; tekst[i] != '\0'; i++)
	{
		if (tekst[i] == stary_znak)
		{
			tekst[i] = nowy_znak;
		}
	}
}

void dolacz_tekst(char *tekst1, const char *tekst2)
{
	strcat(tekst1, tekst2);
}

void dolacz_od_pozycji(char *tekst1, const char *tekst2, int pozycja)
{
	if (pozycja < strlen(tekst2))
	{
		strcat(tekst1, &tekst2[pozycja]);
	}
}

void cykliczne_przesuniecie(int tablica[], int n)
{
	int pierwszy = tablica[0];

	for (int i = 0; i < n - 1; i++)
	{
		tablica[i] = tablica[i + 1];
	}

	tablica[n - 1] = pierwszy;
}

int moje_strcmp(const char *s1, const char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}

	return *(unsigned char *)s1 - *(unsigned char *)s2;
}

char* moje_strcat(char *dest, const char *src)
{
	char *d = dest;
	while (*d) d++;
	while ((*d++ = *src++));
	return dest;
}

char* moje_strcpy(char *dest, const char *src)
{
	char *d = dest;
	while ((*d++ = *src++));
	return dest;
}

int main()
{
	const char *tekst = "Witaj, świecie!";
	char znak = 'j';
	int pozycja = znajdz_pozycje_znaku(tekst, znak);
	printf("Pozycja znaku '%c': %d\n", znak, pozycja);

	char tekst2[] = "Witaj, świecie!";
	usun_pierwsze_wystapienie(tekst2, 'j');
	printf("Po usunięciu pierwszego wystąpienia: %s\n", tekst2);

	char tekst3[] = "Witaj, świecie!";
	zamien_znak(tekst3, 'i', 'o');
	printf("Po zamianie: %s\n", tekst3);

	char tekst4[100] = "Witaj, ";
	dolacz_tekst(tekst4, "świecie!");
	printf("Po dołączeniu: %s\n", tekst4);

	char tekst5[100] = "Witaj, ";
	dolacz_od_pozycji(tekst5, "świecie!", 3);
	printf("Po dołączeniu od pozycji: %s\n", tekst5);

	int tablica[] = {1, 2, 3, 4, 5};
	int n = sizeof(tablica) / sizeof(tablica[0]);
	cykliczne_przesuniecie(tablica, n);
	printf("Po cyklicznym przesunięciu: ");
	for (int i = 0; i < n; i++)
	{
		printf("%d ", tablica[i]);
	}
	printf("\n");

	printf("moje_strcmp(\"abc\", \"abc\"): %d\n", moje_strcmp("abc", "abc"));
	printf("moje_strcmp(\"abc\", \"abd\"): %d\n", moje_strcmp("abc", "abd"));

	char dest[100] = "Witaj, ";
	moje_strcat(dest, "świecie!");
	printf("moje_strcat: %s\n", dest);

	char dest2[100];
	moje_strcpy(dest2, "Test kopiowania");
	printf("moje_strcpy: %s\n", dest2);
}
