#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

jmp_buf exit_program;

extern double max_norm(const double *vector, int size, char op1, int op2, const int square);

void error (char *msg)
{
    fprintf(stderr, "\n%s\nStopping program execution and the validation of other arguments.", msg);

    Sleep(500);

    longjmp(exit_program, 1);
}

void print_matrix (const double *matrix, const int size, const int square)
{

    printf("Loaded matrix:\n");

    if (square == 0)
    {
        for (int j = 0; j < size; j++)
        {
            printf("%.3lf ", matrix[j]);
        }
    }
    else
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                printf("%.3lf ", matrix[i * size + j]);
            }

            printf("\n");
        }
    }

    printf("\n");
}

// double *file_to_matrix (FILE *file, const int size, const int square, const int skip)
// {
//     // Calculate the expected number of elements
//     const int expected_count = square == 1 ? size * size : size;
//
//     double *temp_buffer = malloc(1024 * sizeof(double));
//     if (!temp_buffer)
//     {
//         error("Temporary buffer memory allocation failed.");
//     }
//
//     int actual_count = 0;
//     while (fscanf(file, "%lf", &temp_buffer[actual_count]) == 1)
//     {
//         actual_count++;
//     }
//
//     if (actual_count - skip < expected_count)
//     {
//         free(temp_buffer);
//         char error_message[128];
//
//         if (square == 1)
//         {
//             snprintf(error_message, sizeof(error_message),
//              "File does not contain enough elements for a %dx%d matrix (expected %d, found %d).",
//              size, size, expected_count, actual_count - skip);
//         }
//         else
//         {
//             snprintf(error_message, sizeof(error_message),
//          "File does not contain enough elements for a %d vector (expected %d, found %d).",
//          size, size, expected_count, actual_count - skip);
//         }
//
//         error(error_message);
//     }
//
//     if (actual_count - skip > expected_count)
//     {
//         free(temp_buffer);
//         char error_message[128];
//         if (square == 1)
//         {
//             snprintf(error_message, sizeof(error_message),
//                "File contains more elements than expected for a %dx%d matrix (expected %d, found %d).",
//                size, size, expected_count, actual_count - skip);
//         }
//         else
//         {
//             snprintf(error_message, sizeof(error_message),
//                 "File contains more elements than expected for a %d vector (expected %d, found %d).",
//                 size, size, expected_count, actual_count - skip);
//         }
//
//         error(error_message);
//     }
//
//     double *matrix = malloc(expected_count * sizeof(double));
//     if (!matrix)
//     {
//         free(temp_buffer);
//         error("Matrix memory allocation failed.");
//     }
//
//     for (int i = 0; i < expected_count; i++)
//     {
//         printf("%lf ", temp_buffer[i + skip]);
//         matrix[i] = temp_buffer[i + skip];
//     }
//
//     free(temp_buffer);
//
//     rewind(file);
//
//     print_matrix(matrix, size, square);
//
//     printf("\n");
//
//     return matrix;
// }

double *file_to_matrix(FILE *file, const int size, const int square, const int skip)
{
    // Calculate the expected number of elements
    const int expected_count = square == 1 ? size * size : size;

    double *temp_buffer = malloc(1024 * sizeof(double));
    if (!temp_buffer)
    {
        error("Temporary buffer memory allocation failed.");
    }

    char line[512];
    int actual_count = 0;
    int line_count = 0;

    while (fgets(line, sizeof(line), file))
    {
        line_count++;
        char *ptr = line;
        double value;
        int items_on_line = 0;

        // Parse numbers from the current line
        while (sscanf(ptr, "%lf", &value) == 1)
        {
            if (actual_count - skip >= expected_count)
            {
                free(temp_buffer);
                char error_message[128];

                if (square)
                {
                    snprintf(error_message, sizeof(error_message),
                             "File contains more elements than expected for a %dx%d matrix (expected %d, found more by line %d).",
                             size, size, expected_count, line_count);
                }
                else
                {
                    snprintf(error_message, sizeof(error_message),
                             "File contains more elements than expected for a %d vector (expected %d, found more by line %d).",
                             size, size, expected_count, line_count);
                }

                error(error_message);
            }

            temp_buffer[actual_count++] = value;
            items_on_line++;

            // Move the pointer to the next number in the line
            while (*ptr && !isspace(*ptr)) ptr++;
            while (*ptr && isspace(*ptr)) ptr++;
        }

        if (items_on_line > 0 && actual_count - skip == expected_count)
        {
            break;
        }
    }

    if (actual_count - skip < expected_count)
    {
        free(temp_buffer);
        char error_message[128];

        if (square)
        {
            snprintf(error_message, sizeof(error_message),
                 "File does not contain enough elements for a %dx%d matrix (expected %d, found %d).",
                 size, size, expected_count, actual_count);
        }
        else
        {
            snprintf(error_message, sizeof(error_message),
                 "File does not contain enough elements for a %d vector (expected %d, found %d).",
                 size, size, expected_count, actual_count);
        }

        error(error_message);
    }

    double *matrix = malloc(expected_count * sizeof(double));
    if (!matrix)
    {
        free(temp_buffer);
        error("Matrix memory allocation failed.");
    }

    for (int i = 0; i < expected_count; i++)
    {
        matrix[i] = temp_buffer[i + skip];
    }

    free(temp_buffer);

    rewind(file);

    print_matrix(matrix, size, square);

    printf("\n");

    return matrix;
}


int main (const int argc, const char **argv)
{
    int N = 0;
    FILE *file = nullptr;
    double *matrix = nullptr;
    double *matrix2 = nullptr;

    if (setjmp(exit_program) != 0)
    {
        free(matrix);
        free(matrix2);
        printf("\n");
        system("pause");
        exit(1);
    }

    // Make Polish symbols appear
    system("chcp 65001 > nul");

    if (argc != 2)
    {
        error("Program takes in only 1 argument - the file path. (it is required)");
    }

    file = fopen(argv[1], "r");

    if (file == NULL)
    {
        error("Error opening file");
    }

    printf("Give the number of elements in the vector:\n");
    scanf("%d", &N);

    if (N <= 0)
    {
        error("Improper value given for the number of elements.");
    }

    matrix2 = file_to_matrix(file, N, 0, 0);
    matrix = file_to_matrix(file, N, 1, N);

    printf("Choose how you want to calculate maximum norm:\n");
    printf("1. From all elements in the k-th row of the matrix.\n");
    printf("2. From all elements in the k-th column of the matrix.\n");
    printf("3. From all elements in the main diagonal of the matrix.\n");
    printf("4. From all elements of the matrix that are greater than 0.\n");
    printf("5. From all elements above the main diagonal of the matrix.\n");

    // Clear input buffer
    while (getchar() != '\n' && !feof(stdin)) {};

    const int choice = getchar();

    const auto final_result = (char *)malloc(512 * sizeof(char));

    if (!final_result)
    {
        error("Memory allocation failed.");
    }

    int op2 = -1;
    switch ((char)choice)
    {
        case '1':
        {
            int row = 0;
            strcpy(final_result, "k-th row");

            printf("Which row do you want to choose?\n");
            scanf("%d", &row);

            if (row < 1 || row > N)
            {
                error("Chosen row does not exist!");
            }

            op2 = row;
        }
        break;

        case '2':
        {
            int column = 0;
            strcpy(final_result, "k-th column");

            printf("Which column do you want to choose?\n");
            scanf("%d", &column);

            if (column < 1 || column > N)
            {
                error("Chosen column does not exist!");
            }

            op2 = column;
        }
        break;

        case '3':
        {
            strcpy(final_result, "main diagonal");
        }
        break;

        case '4':
        {
            strcpy(final_result, "elements greater than 0 elements");
        }
        break;

        case '5':
        {
            strcpy(final_result, "above main diagonal");
        }
        break;

        default:
        {
            error("Invalid option chosen.");
        }
    }

    const double result1 = max_norm(matrix2, N, (char)choice, op2, 0);
    const double result2 = max_norm(matrix, N, (char)choice, op2, 1);

    if (result1 == -1)
    {
        printf("Vector option max norm does not exist.\n");
    }
    else
    {
        printf("Vector option max norm is %.3lf\n", result1);
    }

    if (result2 == -1)
    {
        printf("The maximum norm of the %s of the matrix does not exist.\n", final_result);
    }
    else
    {
        printf("The maximum norm of the %s of the matrix is %.3lf.\n", final_result, result2);
    }


    free(matrix);
    free(matrix2);
    free(final_result);

    fclose(file);

    system("pause");

    return 0;
}
