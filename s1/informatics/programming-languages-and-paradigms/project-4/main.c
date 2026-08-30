#include <stdio.h>
#include <stdlib.h>
#include <string.h>


/**
 * "Classes"
 */
typedef struct student
{
    int   year;
    char* name;
    char* surname;

    struct student* next;
    struct student* prev;
} STUDENT;

typedef struct
{
    STUDENT* head;
    STUDENT* tail;
} DOUBLY_LINKED_LIST;

typedef struct
{
    STUDENT** array;
    int       size;
    int       capacity;
} DYNAMIC_ARRAY;

enum Menu
{
    ADD,
    RETRIEVE,
    SEARCH,
    DISPLAY_ALL,
    COUNT_ALL,
    FREE_MEMORY,
    WRITE_BIN_FILE,
    READ_BIN_FILE,
    EXIT
};

void resize_array(DYNAMIC_ARRAY* da)
{
    if (da->size == da->capacity)
    {
        da->capacity *= 2;
        da->array = realloc(da->array, da->capacity * sizeof(STUDENT*));
    }
}

void stack_list_add(DOUBLY_LINKED_LIST* list, STUDENT* student);
void queue_list_add(DOUBLY_LINKED_LIST* list, STUDENT* student);
void stack_array_add(DYNAMIC_ARRAY* da, STUDENT* student);
void queue_array_add(DYNAMIC_ARRAY* da, STUDENT* student);

void load_data(FILE*          file, const int structure_choice, const int stack_or_queue, DOUBLY_LINKED_LIST* list,
               DYNAMIC_ARRAY* da)
{
    char buffer[256];

    while (fgets(buffer, sizeof(buffer), file))
    {
        STUDENT* new_student = malloc(sizeof(STUDENT));
        if (!new_student)
        {
            perror("Memory allocation failed");
            exit(EXIT_FAILURE);
        }

        int  year;
        char name[256];
        char surname[256];
        if (sscanf(buffer, "%s %s %d", name, surname, &year) != 3)
        {
            fprintf(stderr, "Error parsing data file: %s\n", buffer);
            free(new_student);
            continue;
        }

        new_student->name    = strdup(name);
        new_student->surname = strdup(surname);
        new_student->year    = year;
        new_student->next    = nullptr;
        new_student->prev    = nullptr;

        printf("Year: %d, Name: %s, Surname: %s\n", new_student->year, new_student->name, new_student->surname);

        if (structure_choice == 0) // Dynamic Array
        {
            // Stack
            if (stack_or_queue == 0)
            {
                stack_array_add(da, new_student);
            }
            else // Queue
            {
                queue_array_add(da, new_student);
            }
        }
        else // Doubly-Linked List
        {
            // Stack
            if (stack_or_queue == 0)
            {
                stack_list_add(list, new_student);
            }
            else // Queue
            {
                queue_list_add(list, new_student);
            }
        }
    }
}

/**
 * "Methods"
 */
// Doubly-Linked List - STACK
void stack_list_add(DOUBLY_LINKED_LIST* list, STUDENT* student)
{
    if (!list->head)
    {
        list->head = student;
        list->tail = student;
    }
    else
    {
        student->next    = list->head;
        list->head->prev = student;
        list->head       = student;
    }
}

STUDENT* stack_list_retrieve(DOUBLY_LINKED_LIST* list)
{
    if (!list->head)
    {
        return nullptr;
    }

    STUDENT* top = list->head;
    list->head   = list->head->next;
    if (list->head)
    {
        list->head->prev = nullptr;
    }
    else
    {
        list->tail = nullptr;
    }

    return top;
}

// Doubly-Linked List - QUEUE
void queue_list_add(DOUBLY_LINKED_LIST* list, STUDENT* student)
{
    if (!list->tail)
    {
        list->head = student;
        list->tail = student;
    }
    else
    {
        student->prev    = list->tail;
        list->tail->next = student;
        list->tail       = student;
    }
}

STUDENT* queue_list_retrieve(DOUBLY_LINKED_LIST* list)
{
    if (!list->head)
    {
        return nullptr;
    }

    STUDENT* front = list->head;
    list->head     = list->head->next;
    if (list->head)
    {
        list->head->prev = nullptr;
    }
    else
    {
        list->tail = nullptr;
    }

    return front;
}

// Dynamic Array - STACK
void stack_array_add(DYNAMIC_ARRAY* da, STUDENT* student)
{
    resize_array(da);
    da->array[da->size++] = student;
}

STUDENT* stack_array_retrieve(DYNAMIC_ARRAY* da)
{
    if (da->size == 0)
    {
        return nullptr;
    }

    return da->array[--da->size];
}

// Dynamic Array - QUEUE
void queue_array_add(DYNAMIC_ARRAY* da, STUDENT* student)
{
    resize_array(da);
    da->array[da->size++] = student;
}

STUDENT* queue_array_retrieve(DYNAMIC_ARRAY* da)
{
    if (da->size == 0)
    {
        return nullptr;
    }

    STUDENT* front = da->array[0];
    for (int i = 1; i < da->size; i++)
    {
        da->array[i - 1] = da->array[i];
    }

    da->size--;
    return front;
}

STUDENT* create_student(const int year, const char* name, const char* surname)
{
    STUDENT* new_student = malloc(sizeof(STUDENT));

    new_student->year    = year;
    new_student->name    = strdup(name);
    new_student->surname = strdup(surname);
    new_student->next    = nullptr;
    new_student->prev    = nullptr;

    return new_student;
}

void display_students_list(const DOUBLY_LINKED_LIST* list)
{
    const STUDENT* current = list->head;

    while (current)
    {
        printf("Year: %d, Name: %s, Surname: %s\n", current->year, current->name, current->surname);
        current = current->next;
    }
}

void display_students_array(const DYNAMIC_ARRAY* da)
{
    for (int i = 0; i < da->size; i++)
    {
        printf("Year: %d, Name: %s, Surname: %s\n", da->array[i]->year, da->array[i]->name, da->array[i]->surname);
    }
}


/**
 * Main
 */
void search_students(const int structure_choice, const DOUBLY_LINKED_LIST* list, const DYNAMIC_ARRAY* da)
{
    int search_choice;

    printf("\nSearch by:\n");
    printf("0: Year\n");
    printf("1: Name\n");
    printf("2: Surname\n");
    printf("Your choice: ");
    scanf("%d", &search_choice);

    char search_term[256];
    int  search_year = 0;

    if (search_choice == 0)
    {
        printf("Enter year: ");
        scanf("%d", &search_year);
    }
    else if (search_choice == 1 || search_choice == 2)
    {
        printf("Enter %s: ", search_choice == 1 ? "name" : "surname");
        scanf("%s", search_term);
    }
    else
    {
        printf("Invalid choice.\n");
        return;
    }

    int found = 0;
    printf("Searching...\n");

    // Dynamic Array
    if (structure_choice == 0)
    {
        STUDENT** temp_array = malloc(da->size * sizeof(STUDENT*));

        for (int i = 0; i < da->size; i++)
        {
            temp_array[i] = da->array[i];
        }

        for (int i = 0; i < da->size - 1; i++)
        {
            for (int j = 0; j < da->size - i - 1; j++)
            {
                if (strcmp(temp_array[j]->surname, temp_array[j + 1]->surname) > 0)
                {
                    STUDENT* temp     = temp_array[j];
                    temp_array[j]     = temp_array[j + 1];
                    temp_array[j + 1] = temp;
                }
            }
        }

        for (int i = 0; i < da->size; i++)
        {
            int matches = 0;

            if (search_choice == 0 && temp_array[i]->year == search_year)
            {
                matches = 1;
            }
            else if (search_choice == 1 && strcmp(temp_array[i]->name, search_term) == 0)
            {
                matches = 1;
            }
            else if (search_choice == 2 && strcmp(temp_array[i]->surname, search_term) == 0)
            {
                matches = 1;
            }

            if (matches)
            {
                printf("Found -> Year: %d, Name: %s, Surname: %s\n",
                       temp_array[i]->year, temp_array[i]->name, temp_array[i]->surname);
                found = 1;
            }
        }

        free(temp_array);
    }
    else // Doubly-Linked List
    {
        const STUDENT* current = list->head;
        while (current)
        {
            int matches = 0;
            if (search_choice == 0 && current->year == search_year)
            {
                matches = 1;
            }
            else if (search_choice == 1 && strcmp(current->name, search_term) == 0)
            {
                matches = 1;
            }
            else if (search_choice == 2 && strcmp(current->surname, search_term) == 0)
            {
                matches = 1;
            }

            if (matches)
            {
                printf("Found -> Year: %d, Name: %s, Surname: %s\n",
                       current->year, current->name, current->surname);
                found = 1;
            }

            current = current->next;
        }
    }

    if (!found)
    {
        printf("No matching student found.\n");
    }
}

void write_bin_file(const char*          filename, const int structure_choice, const DOUBLY_LINKED_LIST* list,
                    const DYNAMIC_ARRAY* da)
{
    FILE* file = fopen(filename, "wb");
    if (!file)
    {
        perror("Error opening file for writing");
        return;
    }

    // Dynamic Array
    if (structure_choice == 0)
    {
        fwrite(&da->size, sizeof(int), 1, file);

        for (int i = 0; i < da->size; i++)
        {
            const STUDENT* student = da->array[i];
            fwrite(&student->year, sizeof(int), 1, file);

            size_t name_len = strlen(student->name) + 1;
            fwrite(&name_len, sizeof(size_t), 1, file);
            fwrite(student->name, sizeof(char), name_len, file);

            size_t surname_len = strlen(student->surname) + 1;
            fwrite(&surname_len, sizeof(size_t), 1, file);
            fwrite(student->surname, sizeof(char), surname_len, file);
        }
    }
    else // Doubly-Linked List
    {
        int            count   = 0;
        const STUDENT* current = list->head;
        while (current)
        {
            count++;
            current = current->next;
        }

        fwrite(&count, sizeof(int), 1, file);

        current = list->head;
        while (current)
        {
            fwrite(&current->year, sizeof(int), 1, file);

            size_t name_len = strlen(current->name) + 1;
            fwrite(&name_len, sizeof(size_t), 1, file);
            fwrite(current->name, sizeof(char), name_len, file);

            size_t surname_len = strlen(current->surname) + 1;
            fwrite(&surname_len, sizeof(size_t), 1, file);
            fwrite(current->surname, sizeof(char), surname_len, file);

            current = current->next;
        }
    }

    fclose(file);
    printf("Data saved to binary file.\n");
}

void read_bin_file(const char* filename, const int structure_choice, const int stack_or_queue, DOUBLY_LINKED_LIST* list,
                   DYNAMIC_ARRAY* da)
{
    FILE* file = fopen(filename, "rb");
    if (!file)
    {
        perror("Error opening file for reading");
        return;
    }

    // Dynamic Array
    if (structure_choice == 0)
    {
        int size;
        fread(&size, sizeof(int), 1, file);
        da->size = size;

        for (int i = 0; i < size; i++)
        {
            STUDENT* new_student = malloc(sizeof(STUDENT));
            if (!new_student)
            {
                perror("Memory allocation failed");
                exit(EXIT_FAILURE);
            }

            fread(&new_student->year, sizeof(int), 1, file);

            size_t name_len;
            fread(&name_len, sizeof(size_t), 1, file);
            new_student->name = malloc(name_len);
            fread(new_student->name, sizeof(char), name_len, file);

            size_t surname_len;
            fread(&surname_len, sizeof(size_t), 1, file);
            new_student->surname = malloc(surname_len);
            fread(new_student->surname, sizeof(char), surname_len, file);

            new_student->next = nullptr;
            new_student->prev = nullptr;

            if (stack_or_queue == 0)
            {
                stack_array_add(da, new_student);
            }
            else
            {
                queue_array_add(da, new_student);
            }
        }
    }
    else // Doubly-Linked List
    {
        int size;
        fread(&size, sizeof(int), 1, file);

        for (int i = 0; i < size; i++)
        {
            STUDENT* new_student = malloc(sizeof(STUDENT));
            if (!new_student)
            {
                perror("Memory allocation failed");
                exit(EXIT_FAILURE);
            }

            fread(&new_student->year, sizeof(int), 1, file);

            size_t name_len;
            fread(&name_len, sizeof(size_t), 1, file);
            new_student->name = malloc(name_len);
            fread(new_student->name, sizeof(char), name_len, file);

            size_t surname_len;
            fread(&surname_len, sizeof(size_t), 1, file);
            new_student->surname = malloc(surname_len);
            fread(new_student->surname, sizeof(char), surname_len, file);

            new_student->next = nullptr;
            new_student->prev = nullptr;

            if (stack_or_queue == 0)
            {
                stack_list_add(list, new_student);
            }
            else
            {
                queue_list_add(list, new_student);
            }
        }
    }

    fclose(file);
    printf("Data loaded from binary file.\n");
}

void display_current_mode(const int structure_choice, const int stack_or_queue)
{
    const char* structure = structure_choice == 0 ? "Array" : "List";
    const char* behavior  = stack_or_queue == 0 ? "Stack" : "Queue";

    printf("\nCurrent Mode: %s %s", structure, behavior);
}

int main()
{
    DOUBLY_LINKED_LIST list = {
        nullptr,
        nullptr
    };

    DYNAMIC_ARRAY da = {
        malloc(10 * sizeof(STUDENT*)), 0, 10
    };

    int stack_or_queue   = -1;
    int structure_choice = -1;

    printf("Choose type: 0 for Stack, 1 for Queue:\n");
    scanf("%d", &stack_or_queue);

    if (stack_or_queue > 1 || stack_or_queue < 0)
    {
        printf("Invalid option.\n");
        return 1;
    }

    printf("Choose structure: 0 for Array, 1 for List:\n");
    scanf("%d", &structure_choice);

    if (structure_choice > 1 || structure_choice < 0)
    {
        printf("Invalid option.\n");
        return 1;
    }

    // Load data from file
    FILE* file = fopen("../data.txt", "r");
    if (file)
    {
        printf("Loading data from ../data.txt...\n");
        load_data(file, structure_choice, stack_or_queue, &list, &da);
        fclose(file);
        printf("Data loaded successfully.\n");
    }
    else
    {
        printf("No initial data loaded (../data.txt not found).\n");
    }

    int choice = -1;

    // ReSharper disable once CppDFAEndlessLoop
    do
    {
        display_current_mode(structure_choice, stack_or_queue);

        printf("\nSelect an operation:\n");
        printf("0: Add element\n");
        printf("1: Retrieve element\n");
        printf("2: Search element by field\n");
        printf("3: Display all elements\n");
        printf("4: Count elements\n");
        printf("5: Free memory\n");
        printf("6: Save to file (binary)\n");
        printf("7: Load from file (binary)\n");
        printf("8: Exit\n");
        printf("Your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case ADD:
            {
                int  year;
                char name[256];
                char surname[256];

                printf("Enter year: ");
                scanf("%d", &year);

                printf("Enter name: ");
                scanf("%s", name);

                printf("Enter surname: ");
                scanf("%s", surname);

                STUDENT* new_student = create_student(year, name, surname);

                if (structure_choice == 0 && stack_or_queue == 0)
                {
                    stack_array_add(&da, new_student);
                }
                else if (structure_choice == 0 && stack_or_queue == 1)
                {
                    queue_array_add(&da, new_student);
                }
                else if (structure_choice == 1 && stack_or_queue == 0)
                {
                    stack_list_add(&list, new_student);
                }
                else
                {
                    queue_list_add(&list, new_student);
                }
            }
            break;
            case RETRIEVE:
            {
                STUDENT* student = nullptr;

                if (structure_choice == 0 && stack_or_queue == 0)
                {
                    student = stack_array_retrieve(&da);
                }
                else if (structure_choice == 0 && stack_or_queue == 1)
                {
                    student = queue_array_retrieve(&da);
                }
                else if (structure_choice == 1 && stack_or_queue == 0)
                {
                    student = stack_list_retrieve(&list);
                }
                else
                {
                    student = queue_list_retrieve(&list);
                }

                if (student)
                {
                    printf("Retrieved -> Year: %d, Name: %s, Surname: %s\n", student->year, student->name,
                           student->surname);
                    free(student->name);
                    free(student->surname);
                    free(student);
                }
                else
                {
                    printf("No elements to retrieve.\n");
                }
            }
            break;
            case SEARCH:
            {
                search_students(structure_choice, &list, &da);
            }
            break;
            case DISPLAY_ALL:
            {
                if (structure_choice == 0)
                {
                    display_students_array(&da);
                }
                else
                {
                    display_students_list(&list);
                }
            }
            break;
            case COUNT_ALL:
            {
                int count = 0;

                // Dynamic Array
                if (structure_choice == 0)
                {
                    count = da.size;
                }
                else // Doubly-Linked List
                {
                    const STUDENT* current = list.head;

                    while (current)
                    {
                        count++;
                        current = current->next;
                    }
                }

                printf("Total number of elements: %d\n", count);
            }
            break;
            case FREE_MEMORY:
            {
                // Dynamic Array
                if (structure_choice == 0)
                {
                    for (int i = 0; i < da.size; i++)
                    {
                        free(da.array[i]->name);
                        free(da.array[i]->surname);
                        free(da.array[i]);
                    }

                    free(da.array);
                    da.array    = malloc(10 * sizeof(STUDENT*)); // Reset array
                    da.size     = 0;
                    da.capacity = 10;

                    printf("Dynamic Array cleared successfully.\n");
                }
                else // Doubly-Linked List
                {
                    STUDENT* current = list.head;

                    while (current)
                    {
                        STUDENT* next = current->next;
                        free(current->name);
                        free(current->surname);
                        free(current);
                        current = next;
                    }

                    list.head = nullptr;
                    list.tail = nullptr;

                    printf("Doubly-Linked List cleared successfully.\n");
                }
            }
            break;
            case WRITE_BIN_FILE:
            {
                char filename[256];
                printf("Enter filename: ");
                scanf("%s", filename);

                write_bin_file(filename, structure_choice, &list, &da);
            }
            break;
            case READ_BIN_FILE:
            {
                char filename[256];
                printf("Enter filename: ");
                scanf("%s", filename);

                read_bin_file(filename, structure_choice, stack_or_queue, &list, &da);
            }
            break;

            case EXIT:
            {
                printf("Exiting...\n");
            }
            break;
            default:
            {
                printf("Invalid choice. Try again.\n");
            }
        }
    }
    while (choice != EXIT);

    return 0;
}
