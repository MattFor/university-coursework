#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stud
{
    char* imie;
    char* nazwisko;
    int rok;
    char* adres;
    double stypendium;
    struct stud* n;
} STUDENT;

STUDENT * head = NULL;

void list1(FILE * plik)
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

        new_student->n = head;
        head = new_student;
    }
}

void dispList1()
{
    STUDENT * temp = head;
    while (temp != NULL)
    {
        printf("Imię: %s, Nazwisko: %s, Rok urodzenia: %d, Adres: %s, Stypendium: %.2f\n",
            temp -> imie, temp -> nazwisko, temp -> rok, temp -> adres, temp -> stypendium);

        temp = temp -> n;
    }
}

STUDENT * max_s()
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

void addHeadList1(char * imie, char * nazwisko, int rok, char * adres, double stypendium)
{
    STUDENT * new_student = (STUDENT * ) malloc(sizeof(STUDENT));
    new_student -> imie = strdup(imie);
    new_student -> nazwisko = strdup(nazwisko);
    new_student -> rok = rok;
    new_student -> adres = strdup(adres);
    new_student -> stypendium = stypendium;
    new_student -> n = head;
    head = new_student;
}

void addTailList1(char * imie, char * nazwisko, int rok, char * adres, double stypendium)
{
    STUDENT * new_student = (STUDENT * ) malloc(sizeof(STUDENT));
    new_student -> imie = strdup(imie);
    new_student -> nazwisko = strdup(nazwisko);
    new_student -> rok = rok;
    new_student -> adres = strdup(adres);
    new_student -> stypendium = stypendium;
    new_student -> n = NULL;

    if (head == NULL)
    {
        head = new_student;
    }
    else
    {
        STUDENT * temp = head;

        while (temp -> n != NULL)
        {
            temp = temp -> n;
        }

        temp -> n = new_student;
    }
}

int lenList1()
{
    int count = 0;
    STUDENT * temp = head;

    while (temp != NULL)
    {
        count++;
        temp = temp -> n;
    }

    return count;
}

void remHeadList1()
{
    if (head != NULL)
  	{
        STUDENT * temp = head;
        head = head -> n;
        free(temp -> imie);
        free(temp -> nazwisko);
        free(temp -> adres);
        free(temp);
    }
}

void remTailList1()
{
    if (head != NULL)
  	{
        if (head -> n == NULL)
      	{
            free(head -> imie);
            free(head -> nazwisko);
            free(head -> adres);
            free(head);
            head = NULL;
        }
        else
        {
            STUDENT * temp = head;
            while (temp -> n -> n != NULL)
            {
                temp = temp -> n;
            }

            free(temp -> n -> imie);
            free(temp -> n -> nazwisko);
            free(temp -> n -> adres);
            free(temp -> n);
            temp -> n = NULL;
        }
    }
}