#include <cstdio>
#include <cstdlib>

typedef struct el_listy
{
	int klucz;
	struct el_listy* nast;
} LISTA, * LISTAWSK;

int przegladanie(LISTA* p)
{
	int licznik = 0;
	while (p != nullptr)
	{
		p = p->nast;

		if (p != nullptr)
		{
			licznik++;
			printf("klucz=%d licznik=%d\n", p->klucz, licznik);
		}
	}

	return licznik;
}

void dodaj_za(LISTA* p, int k)
{
	if (p == nullptr)
	{
		printf("Error: nie mozna dodac po nullptr node.\n");
		return;
	}

	LISTA* pom;
	pom = (LISTAWSK) malloc(sizeof(LISTA));
	if (pom == nullptr)
	{
		printf("Error: blad pamieci\n");
		return;
	}

	pom->klucz = k;
	pom->nast = p->nast;
	p->nast = pom;
}

void dodaj_przed(LISTA* p, int k)
{
	if (p == nullptr)
	{
		printf("Error: nie mozna dodac przed nullptr node\n");
		return;
	}

	LISTA* pom;
	pom = (LISTAWSK) malloc(sizeof(LISTA));
	if (pom == nullptr)
	{
		printf("Error: blad pamieci\n");
		return;
	}

	pom->klucz = p->klucz;
	pom->nast = p->nast;

	p->klucz = k;
	p->nast = pom;
}

void usun_nast(LISTA* p)
{
	if (p == nullptr)
	{
		printf("Error:nie mozna usunac nullptr node\n");
		return;
	}

	if (p->nast == nullptr)
	{
		printf("nie ma nastepnego\n");
		return;
	}

	LISTA* pom;
	pom = p->nast;

	p->nast = pom->nast;

	free(pom);
}

void usun(LISTA* glowa, LISTA* p)
{
	if (p == nullptr)
	{
		printf("Error: nie mozna usunac nullptr\n");
		return;
	}

	if (glowa == nullptr)
	{
		printf("Error: nie mozna wykonac funkcji gdy glowa to nullptr\n");
		return;
	}

	LISTA* pom;

	if (p->nast == nullptr)
	{
		if (glowa == p)
		{
		}
		else
		{
			LISTA* pred = glowa;
			while (pred != nullptr && pred->nast != p)
			{
				pred = pred->nast;
			}

			if (pred != nullptr)
			{
				pred->nast = nullptr;
				free(p);
			}
			else
			{
				printf("Error: nie mozna znalezc poprzedniego node-a.\n");
			}
		}
	}
	else
	{
		pom = p->nast;
		*p = *pom;
		free(pom);
	}
}

LISTA* szukaj(LISTA* p, int k)
{
	if (p == nullptr)
	{
		return nullptr;
	}

	while (true)
	{
		if (p->nast == nullptr)
		{
			return nullptr;
		}
		else
		{
			p = p->nast;

			if (p->klucz == k)
			{
				return p;
			}
		}
	}
}

int liczrek(LISTA* p)
{
	if (p->nast == nullptr)
	{
		return 0;
	}
	else
	{
		return 1 + liczrek(p->nast);
	}
}

void przeglrewrek(LISTA* p)
{
	if (p == nullptr)
	{
		return;
	}

	przeglrewrek(p->nast);
	printf("%d  \n", p->klucz);
}

void przeglrek(LISTA* p)
{
	if (p == nullptr)
	{
		return;
	}

	printf("%d  \n", p->klucz);
	przeglrek(p->nast);
}

int maxrek(LISTA* p)
{
	if (p == nullptr)
	{
		return 0;
	}

	if (p->nast == nullptr)
	{
		return p->klucz;
	}

	if (const int max_rest = maxrek(p->nast); p->klucz > max_rest)
	{
		return p->klucz;
	}
	else
	{
		return max_rest;
	}
}

LISTAWSK odwroc(LISTA* p)
{
	LISTAWSK w1 = nullptr;
	LISTAWSK w2 = p;
	LISTAWSK w3 = nullptr;

	while (w2 != nullptr)
	{
		w3 = w2->nast;
		w2->nast = w1;
		w1 = w2;
		w2 = w3;
	}

	return w1;
}

void zamien(int x, int y, LISTA* glowa)
{
	if (glowa == nullptr)
	{
		printf("Error: nie mozna wykonac funkcji na nullptr.\n");
		return;
	}

	LISTA* current = glowa->nast;

	while (current != nullptr)
	{
		if (current->klucz == x)
		{
			current->klucz = y;
		}

		if (current->klucz < x)
		{
			break;
		}

		current = current->nast;
	}
}

int usunx(LISTA* p, int x)
{
	if (p == nullptr)
	{
		return 0;
	}

	if (p->nast == nullptr)
	{
		return 0;
	}

	if (p->nast->klucz == x)
	{
		LISTA* to_remove = p->nast;
		p->nast = p->nast->nast;
		free(to_remove);
		return 1;
	}

	if (p->nast->klucz > x)
	{
		return 0;
	}

	return usunx(p->nast, x);
}

int usun2x(LISTA* p, int x)
{
	if (p == nullptr)
	{
		return 0;
	}

	if (p->nast == nullptr)
	{
		return 0;
	}

	if (p->nast->klucz == x)
	{
		LISTA* to_remove = p->nast;
		p->nast = p->nast->nast;
		free(to_remove);
		return 1;
	}

	if (p->nast->klucz < x)
	{
		return 0;
	}

	return usun2x(p->nast, x);
}

void dodaj_sort(int x, LISTA* g)
{
	if (g == nullptr)
	{
		printf("Error: nie mozna dodac do listy z head nullptr.\n");
		return;
	}

	auto* new_node = (LISTA*) malloc(sizeof(LISTA));
	if (new_node == nullptr)
	{
		printf("Error: blad pamieci\n");
		return;
	}

	new_node->klucz = x;
	LISTA* current = g;

	while (current->nast != nullptr && current->nast->klucz < x)
	{
		current = current->nast;
	}

	new_node->nast = current->nast;
	current->nast = new_node;
}

int main()
{
	int k;
	int x, y;
	LISTA* glowa = nullptr;
	LISTA* ost;

	auto* pom = (LISTA*) malloc(sizeof(LISTA));
	if (pom == nullptr)
	{
		printf("Error: blad pamieci\n");
		return 1;
	}
	pom->klucz = 0;
	pom->nast = nullptr;
	glowa = pom;
	ost = glowa;

	printf("Podaj klucz kolejnego elementu listy (0 - koniec wprowadzania):\n");
	scanf("%d", &k);

	while (k != 0)
	{
		dodaj_za(ost, k);
		ost = ost->nast;
		printf("Podaj klucz kolejnego elementu listy (0 - koniec wprowadzania):\n");
		scanf("%d", &k);
	}

	printf("\n--- Przegladanie listy ---\n");
	przegladanie(glowa);

	printf("\n--- Dlugosc listy (rekurencyjnie) ---\n");
	printf("Dlugosc listy: %d\n", liczrek(glowa));

	printf("\n--- Odwracanie listy (od elementu po glowie) ---\n");
	glowa->nast = odwroc(glowa->nast);
	printf("Lista po odwroceniu:\n");
	przegladanie(glowa);

	printf("\n--- Przegladanie listy (rekurencyjnie) w przod ---\n");
	przeglrek(glowa->nast);

	printf("\n--- Przegladanie listy (rekurencyjnie) w tyl ---\n");
	przeglrewrek(glowa->nast);

	printf("\n--- Maksymalny element (rekurencyjnie) ---\n");
	printf("Maksymalny element: %d\n", maxrek(glowa->nast));

	printf("\n--- Dodawanie elementu do posortowanej rosnaco listy ---\n");
	printf("Dodawanie 5 do listy uzywajac dodaj_sort:\n");
	dodaj_sort(5, glowa);
	przegladanie(glowa);

	printf("Dodawanie 15 do listy uzywajac dodaj_sort:\n");
	dodaj_sort(15, glowa);
	przegladanie(glowa);

	printf("\n--- Zamiana elementu w posortowanej malejaco liscie ---\n");
	glowa->nast = odwroc(glowa->nast);
	przegladanie(glowa);

	printf("napisz klucz do zamienienia (x) i nowy klucz (y) zamien:\n");
	scanf("%d %d", &x, &y);
	zamien(x, y, glowa);
	printf("Lista po zamien:\n");
	przegladanie(glowa);


	printf("\n--- Usuwanie elementu (usunx) z posortowanej rosnaco listy ---\n");
	glowa->nast = odwroc(glowa->nast);
	przegladanie(glowa);

	printf("Napisz klucz do usuniecia za pomoca usunx:\n");
	scanf("%d", &x);

	int removed_count_usunx = usunx(glowa, x);
	if (removed_count_usunx)
	{
		printf("Element z kluczem %d usuniety za pomoca usunx.\n", x);
	}
	else
	{
		printf("Element z kluczem %d nie znaleziony za pomoca usunx.\n", x);
	}

	printf("Lista po usunx:\n");
	przegladanie(glowa);


	printf("\n--- Usuwanie elementu (usun2x) z posortowanej malejaco listy ---\n");
	glowa->nast = odwroc(glowa->nast);
	przegladanie(glowa);

	printf("Napisz klucz do usuniecia uzywajac usun2x:\n");
	scanf("%d", &x);
	int removed_count_usun2x = usun2x(glowa, x);

	if (removed_count_usun2x)
	{
		printf("Element z kluczem %d usuniety za pomoca usun2x.\n", x);
	}
	else
	{
		printf("Element z kluczem %d nie znaleziony za pomoca usun2x.\n", x);
	}

	printf("Lista po usun2x:\n");
	przegladanie(glowa);


	printf("\n--- Zwalnianie pamieci ---\n");
	LISTA* current = glowa;
	while (current != nullptr)
	{
		LISTA* next = current->nast;
		printf("Zwalnianie pamieci klucza: %d\n", current->klucz);
		free(current);
		current = next;
	}

	printf("Czyszczenie pamieci zakonczone.\n");

	printf("\nNacisnij enter by zakonczyc.");
	getchar();
	getchar();

	return 0;
}