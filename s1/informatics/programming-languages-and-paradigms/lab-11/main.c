#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stud
{
    char * imie;
    char * nazwisko;
    int rok;
    char * adres;
    double stypendium;
    struct stud * p;
    struct stud * n;
}
STUDENT;

STUDENT * head = nullptr;
STUDENT * tail = nullptr;

void list2(FILE * plik)
{
    char buffer[256];

    while (fgets(buffer, sizeof(buffer), plik))
    {
        const auto new_student = (STUDENT*)malloc(sizeof(STUDENT));
        if (!new_student)
        {
            perror("Błąd alokacji pamięci");
            exit(EXIT_FAILURE);
        }

        buffer[strcspn(buffer, "\n")] = '\0';
        new_student->imie = strdup(buffer);

        fgets(buffer, sizeof(buffer), plik);
        buffer[strcspn(buffer, "\n")] = '\0';
        new_student->nazwisko = strdup(buffer);

        fgets(buffer, sizeof(buffer), plik);
        new_student->rok = atoi(buffer);

        fgets(buffer, sizeof(buffer), plik);
        buffer[strcspn(buffer, "\n")] = '\0';
        new_student->adres = strdup(buffer);

        fgets(buffer, sizeof(buffer), plik);
        new_student->stypendium = atof(buffer);

        new_student->n = nullptr;
        new_student->p = tail;

        if (tail != nullptr)
        {
            tail->n = new_student;
        }

        tail = new_student;

        if (head == nullptr)
        {
            head = new_student;
        }
    }
}

void dispList2()
{
    const STUDENT * temp = head;
    while (temp != nullptr)
    {
        printf("Imię: %s, Nazwisko: %s, Rok urodzenia: %d, Adres: %s, Stypendium: %.2f\n",
            temp -> imie, temp -> nazwisko, temp -> rok, temp -> adres, temp -> stypendium);

        temp = temp -> n;
    }
}

STUDENT * max_s2()
{
    STUDENT * temp = head;
    STUDENT * max_student = nullptr;
    double max_stypendium = -1.0;

    while (temp != nullptr)
    {
        if (temp -> stypendium > max_stypendium)
        {
            max_stypendium = temp -> stypendium;
            max_student = temp;
        }

        temp = temp -> n;
    }

    return max_student;
}

void addHeadList2(const char * imie, const char * nazwisko, const int rok, const char * adres, const double stypendium)
{
    const auto new_student = (STUDENT * ) malloc(sizeof(STUDENT));
    new_student -> imie = strdup(imie);
    new_student -> nazwisko = strdup(nazwisko);
    new_student -> rok = rok;
    new_student -> adres = strdup(adres);
    new_student -> stypendium = stypendium;
    new_student -> n = head;
    new_student -> p = nullptr;

    if (head != nullptr)
    {
        head -> p = new_student;
    }

    head = new_student;

    if (tail == nullptr)
    {
        tail = new_student;
    }
}

void addTailList2(const char * imie, const char * nazwisko, const int rok, const char * adres, const double stypendium)
{
    const auto new_student = (STUDENT * ) malloc(sizeof(STUDENT));
    new_student -> imie = strdup(imie);
    new_student -> nazwisko = strdup(nazwisko);
    new_student -> rok = rok;
    new_student -> adres = strdup(adres);
    new_student -> stypendium = stypendium;
    new_student -> n = nullptr;
    new_student -> p = tail;

    if (tail != nullptr)
    {
        tail -> n = new_student;
    }

    tail = new_student;

    if (head == nullptr)
    {
        head = new_student;
    }
}

void remHeadList2()
{
    if (head != nullptr)
    {
        STUDENT * temp = head;
        head = head -> n;
        if (head != nullptr)
        {
            head -> p = nullptr;
        }

        free(temp -> imie);
        free(temp -> nazwisko);
        free(temp -> adres);
        free(temp);
    }
}

void remTailList2()
{
    if (tail != nullptr)
    {
        STUDENT * temp = tail;
        tail = tail -> p;
        if (tail != nullptr)
        {
            tail -> n = nullptr;
        }

        free(temp -> imie);
        free(temp -> nazwisko);
        free(temp -> adres);
        free(temp);
    }
}

void swap_students (STUDENT *A1, STUDENT *A2)
{
	double temp_stypendium = A1->stypendium;
	A1->stypendium = A2->stypendium;
	A2->stypendium = temp_stypendium;

	char *temp_imie = A1->imie;
	A1->imie = A2->imie;
	A2->imie = temp_imie;

	char *temp_nazwisko = A1->nazwisko;
	A1->nazwisko = A2->nazwisko;
	A2->nazwisko = temp_nazwisko;

	int temp_rok = A1->rok;
	A1->rok = A2->rok;
	A2->rok = temp_rok;

	char *temp_adres = A1->adres;
	A1->adres = A2->adres;
	A2->adres = temp_adres;
}

int compare_by_scholarship(STUDENT *a, STUDENT *b)
{
	if (a->stypendium < b->stypendium) return 1;
	if (a->stypendium > b->stypendium) return -1;
	return 0;
}

int compare_by_name(STUDENT *a, STUDENT *b)
{
	return strcmp(a->nazwisko, b->nazwisko);
}

int compare_by_year (STUDENT *a, STUDENT *b)
{
	return a->rok - b->rok;
}

int compare_students (STUDENT *a, STUDENT *b, int (*compare)(STUDENT *, STUDENT *))
{
	return compare(a, b);
}

void sort_list (STUDENT *head, int (*compare)(STUDENT *, STUDENT *))
{
	if (head == nullptr || head->n == nullptr)
	{
		return;
	}

	STUDENT *A1, *A2;
	int swapped;
	do {
		swapped = 0;
		A1 = head;
		while (A1 != nullptr && A1->n != nullptr) {
			A2 = A1->n;
			if (compare(A1, A2) > 0)
			{
				swap_students(A1, A2);
				swapped = 1;
			}
			A1 = A1->n;
		}
	} while (swapped);
}

void zad1()
{
	FILE *file = fopen("../data.txt", "r");
	if (file == nullptr)
	{
		perror("Błąd otwarcia pliku");
		return;
	}

	list2(file);

	printf("Lista przed posortowaniem:\n");
	dispList2();

	sort_list(head, compare_by_name);

	printf("\nLista po posortowaniu według stypendium (malejąco):\n");
	dispList2();

	fclose(file);
}

typedef struct
{
	int dim;
	char str[64];
	double *buff;
} MY_VECTOR;

void initialize_vector (MY_VECTOR *vec, int dim, const char *name, int is_x)
{
	vec->dim = dim;
	strncpy(vec->str, name, sizeof(vec->str) - 1);
	vec->str[sizeof(vec->str) - 1] = '\0';
	vec->buff = (double *)malloc(dim * sizeof(double));

	if (vec->buff == nullptr)
	{
		perror("Błąd alokacji pamięci dla buff");
		exit(EXIT_FAILURE);
	}

	if (is_x)
	{
		for (int i = 0; i < dim; i++)
		{
			vec->buff[i] = 1.0 / (i + 1); // xi = 1/(i+1)
		}
	}
	else
	{
		for (int i = 0; i < dim; i++)
		{
			vec->buff[i] = i + 1; // yi = i+1
		}
	}
}

double dot_product (const MY_VECTOR *vec1, const MY_VECTOR *vec2)
{
	if (vec1->dim != vec2->dim)
	{
		fprintf(stderr, "Wektory mają różne rozmiary!\n");
		exit(EXIT_FAILURE);
	}

	double dot = 0.0;

	for (int i = 0; i < vec1->dim; i++)
	{
		dot += vec1->buff[i] * vec2->buff[i];
	}

	return dot;
}

void free_vector (MY_VECTOR *vec)
{
	free(vec->buff);
	vec->buff = nullptr;
}

void zad2 ()
{
	int n;

	printf("Podaj rozmiar wektorów: ");
	scanf("%d", &n);

	const auto tab = (MY_VECTOR *)malloc(2 * sizeof(MY_VECTOR));
	if (tab == nullptr)
	{
		perror("Błąd alokacji pamięci dla tablicy wektorów");
		return;
	}

	initialize_vector(&tab[0], n, "Wektor X", 1);
	initialize_vector(&tab[1], n, "Wektor Y", 0);

	const double dot = dot_product(&tab[0], &tab[1]);

	printf("Iloczyn skalarny %s i %s wynosi: %.2f\n", tab[0].str, tab[1].str, dot);

	if (dot == (double)n)
	{
		printf("Wynik jest poprawny.\n");
	}
	else
	{
		printf("Wynik jest niepoprawny.\n");
	}

	free_vector(&tab[0]);
	free_vector(&tab[1]);
	free(tab);
}

void zad4 ()
{
	const int SIZE = rand() % 100;

	int array[SIZE];
	int read_array[SIZE];
	const char* filename = "../data.bin";

	for (int i = 0; i < SIZE; i++)
	{
		array[i] = rand() % 100;
	}

	FILE* file = fopen(filename, "wb");
	if (!file)
	{
		perror("Nie można otworzyć pliku do zapisu");
		return 1;
	}

	if (fwrite(array, sizeof(int), SIZE, file) != SIZE)
	{
		perror("Błąd zapisu do pliku");
		fclose(file);
		return 1;
	}

	fclose(file);

	for (int i = 0; i < SIZE; i++)
	{
		array[i] = 0;
	}

	file = fopen(filename, "rb");
	if (!file)
	{
		perror("Nie można otworzyć pliku do odczytu");
		return 1;
	}

	if (fread(read_array, sizeof(int), SIZE, file) != SIZE)
	{
		perror("Błąd odczytu z pliku");
		fclose(file);
		return;
	}

	fclose(file);

	printf("Wczytane dane:\n");
	for (int i = 0; i < SIZE; i++)
	{
		printf("%d ", read_array[i]);
	}

	printf("\n");
}

int main ()
{
	srand(time(nullptr));

	zad1();
	zad2();
	zad4();
}