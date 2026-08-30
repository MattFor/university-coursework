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

STUDENT * head = NULL;
STUDENT * tail = NULL;

void list2(FILE * plik)
{
    char buffer[256];

    while (fgets(buffer, sizeof(buffer), plik))
    {
        STUDENT* new_student = (STUDENT*)malloc(sizeof(STUDENT));
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

        new_student->n = NULL;
        new_student->p = tail;

        if (tail != NULL)
        {
            tail->n = new_student;
        }

        tail = new_student;

        if (head == NULL)
        {
            head = new_student;
        }
    }
}

void dispList2()
{
    STUDENT * temp = head;
    while (temp != NULL)
    {
        printf("Imię: %s, Nazwisko: %s, Rok urodzenia: %d, Adres: %s, Stypendium: %.2f\n",
            temp -> imie, temp -> nazwisko, temp -> rok, temp -> adres, temp -> stypendium);

        temp = temp -> n;
    }
}

STUDENT * max_s2()
{
    STUDENT * temp = head;
    STUDENT * max_student = NULL;
    double max_stypendium = -1.0;

    while (temp != NULL)
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

void addHeadList2(char * imie, char * nazwisko, int rok, char * adres, double stypendium)
{
    STUDENT * new_student = (STUDENT * ) malloc(sizeof(STUDENT));
    new_student -> imie = strdup(imie);
    new_student -> nazwisko = strdup(nazwisko);
    new_student -> rok = rok;
    new_student -> adres = strdup(adres);
    new_student -> stypendium = stypendium;
    new_student -> n = head;
    new_student -> p = NULL;

    if (head != NULL)
    {
        head -> p = new_student;
    }

    head = new_student;

    if (tail == NULL)
    {
        tail = new_student;
    }
}

void addTailList2(char * imie, char * nazwisko, int rok, char * adres, double stypendium)
{
    STUDENT * new_student = (STUDENT * ) malloc(sizeof(STUDENT));
    new_student -> imie = strdup(imie);
    new_student -> nazwisko = strdup(nazwisko);
    new_student -> rok = rok;
    new_student -> adres = strdup(adres);
    new_student -> stypendium = stypendium;
    new_student -> n = NULL;
    new_student -> p = tail;

    if (tail != NULL)
    {
        tail -> n = new_student;
    }

    tail = new_student;

    if (head == NULL)
    {
        head = new_student;
    }
}

void remHeadList2()
{
    if (head != NULL)
    {
        STUDENT * temp = head;
        head = head -> n;
        if (head != NULL)
        {
            head -> p = NULL;
        }

        free(temp -> imie);
        free(temp -> nazwisko);
        free(temp -> adres);
        free(temp);
    }
}

void remTailList2()
{
    if (tail != NULL)
    {
        STUDENT * temp = tail;
        tail = tail -> p;
        if (tail != NULL)
        {
            tail -> n = NULL;
        }

        free(temp -> imie);
        free(temp -> nazwisko);
        free(temp -> adres);
        free(temp);
    }
}