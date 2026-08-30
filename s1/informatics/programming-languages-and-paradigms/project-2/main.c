#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <windows.h>

int bytes_in_char(const int c)
{
    // Operacje na bitach szybsze niż > i <
    // 0xxxxxxx - 1-byte character (ASCII)
    if ((c & 0x80) == 0)
    {
        return 1;
    }

    // 110xxxxx - 2-byte character
    if ((c & 0xE0) == 0xC0)
    {
        return 2;
    }

    // 1110xxxx - 3-byte character
    if ((c & 0xF0) == 0xE0)
    {
        return 3;
    }

    // 11110xxx - 4-byte character
    if ((c & 0xF8) == 0xF0)
    {
        return 4;
    }

    // Unknown symbol
    return -1;
}

void print_header(FILE *output, const char *filename, const int page_number, const int show_exec_time, const int show_file_path, const int show_real_length, const int show_date, const int show_owner, const int real_length, const char *owner, clock_t start_time)
{
    fprintf(output, "=== Strona %d ===\n", page_number);
    printf("=== Strona %d ===\n", page_number);

    if (show_file_path)
    {
        fprintf(output, "Plik: %s\n", filename);
        printf("Plik: %s\n", filename);
    }

    if (show_date)
    {
        const time_t t = time(nullptr);
        const struct tm tm = *localtime(&t);

        fprintf(output, "Data wydruku: %02d-%02d-%d %02d:%02d:%02d\n",
            tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,
            tm.tm_hour, tm.tm_min, tm.tm_sec);
        printf("Data wydruku: %02d-%02d-%d %02d:%02d:%02d\n",
                tm.tm_mday, tm.tm_mon + 1, tm.tm_year + 1900,
                tm.tm_hour, tm.tm_min, tm.tm_sec);
    }

    if (show_owner)
    {
        fprintf(output, "Właściciel: %s\n", owner);
        printf("Właściciel: %s\n", owner);
    }


    if (show_real_length)
    {
        fprintf(output, "Rzeczywista długość (w bajtach): %d\n", real_length);
        printf("Rzeczywista długość (w bajtach): %d\n", real_length);
    }

    if (show_exec_time)
    {
        const clock_t end = clock();
        double time_spent = (double)(end - start_time) / CLOCKS_PER_SEC;

        fprintf(output, "Od uruchomienia programu do wypisania strony upłynęło %.3f sekund\n", time_spent);
        printf("Od uruchomienia programu do wypisania strony upłynęło %.3f sekund\n", time_spent);
    }

    fprintf(output, "===============\n");
    printf("===============\n");
}

int main(const int argc, char *argv[])
{
    // Measure execution time
    const clock_t start_time = clock();

    int exit_status = 0;

    system("chcp 65001 > nul"); // Change to UTF-8 on cmd

    if (strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0)
    {
        fprintf(stderr, "Użycie:\n%s <ścieżka_pliku> <znaki_na_stronę> [-f (ścieżka pliku)] [-d (pokazuje date)] [-o właściciel] [-r (pokazuje rzeczywista długość linii w bajtach)]\n", argv[0]);
        exit_status = 0;
        goto exit;
    }

    if (argc < 3)
    {
        fprintf(stderr, "Program w najmniejszej konfiguracji przyjmuje 2 argumenty, wywołaj poprawnie:\n%s <ścieżka_pliku> <znaki_na_stronę>\nBy dowiedzieć sie więcej, prosze wywołać program z flaga '-h'.\nKoniec dalszego wykonywania programu.\n", argv[0]);
        exit_status = 1;
        goto exit;
    }

    if (argc > 9)
    {
        fprintf(stderr, "Za duża ilość argumentów! Koniec dalszego wykonywania programu i sprawdzania innych argumentów.\nBy dowiedzieć sie więcej, prosze wywołać program z flaga '-h'.\n");
        exit_status = 1;
        goto exit;
    }

    const char *owner = "Nieznany";
    const char *filename = argv[1];

    const size_t filename_len = strlen(filename);
    if (filename_len < 4 || strcasecmp(filename + filename_len - 4, ".txt") != 0)
    {
        fprintf(stderr, "Podany plik nie jest plikiem tekstowym! Koniec dalszego wykonywania programu i sprawdzania innych argumentów.\n");
        exit_status = 1;
        goto exit;
    }

    int show_date = 0;
    int show_owner = 0;
    int show_file_path = 0;
    int show_exec_time = 0;
    int show_real_length = 0;

    char *endptr;
    const long chars_per_page = strtol(argv[2], &endptr, 10); // Base 10

    if (*endptr != '\0' || chars_per_page <= 0)
    {
        fprintf(stderr, "Błąd: 'linie_na_stronę' musi byc dodatnia liczba całkowita! Koniec dalszego wykonywania programu i sprawdzania innych argumentów.\n");
        exit_status = 1;
        goto exit;
    }

    if (chars_per_page == LONG_MAX)
    {
        fprintf(stderr, "Błąd: 'linie_na_stronę' jest zbyt duże! Koniec dalszego wykonywania programu i sprawdzania innych argumentów.\n");
        exit_status = 1;
        goto exit;
    }

    for (int i = 3; i < argc; i++)
    {
        if (strcmp(argv[i], "-d") == 0)
        {
            if (show_date)
            {
                fprintf(stderr, "Zbyt duża ilość wystąpień argumentu '-d'! Koniec dalszego wykonywania programu i sprawdzania innych argumentów.\n");
                exit_status = 1;
                goto exit;
            }

            show_date = 1;
        }
        else if (strcmp(argv[i], "-o") == 0)
        {
            if (show_owner)
            {
                fprintf(stderr, "Zbyt duża ilość wystąpień argumentu '-o'! Koniec dalszego wykonywania programu i sprawdzania innych argumentów.\n");
                exit_status = 1;
                goto exit;
            }

            show_owner = 1;

            const int sys_owner = i + 1 >= argc || strcmp(argv[i + 1], "-d") == 0 || strcmp(argv[i + 1], "-r") == 0;
            if (sys_owner)
            {
                fprintf(stderr, "Uwaga! - użyto flagi '-o' ale nie podano właściciela! Wstawianie właściciela pliku z systemu.\n");
                exit_status = 1;
                goto exit;
                //
                // BOOL bOwnerDefaulted = 0;
                // PSID pOwnerSid = nullptr;
                // PSECURITY_DESCRIPTOR pSD = nullptr;
                //
                // // Get the security descriptor of the file
                // if (GetFileSecurity(filename, OWNER_SECURITY_INFORMATION, pSD, 0, (LPDWORD)&pSD))
                // {
                //     pSD = (PSECURITY_DESCRIPTOR)malloc(dwSize);
                //
                //     if (GetSecurityDescriptorOwner(pSD, &pOwnerSid, &bOwnerDefaulted))
                //     {
                //         // Retrieve the owner name from the SID
                //         char owner_system[256];
                //         SID_NAME_USE sidType;
                //         DWORD size = strlen(owner_system);
                //
                //         if (LookupAccountSid(nullptr, pOwnerSid, owner_system, &size, nullptr, nullptr, &sidType))
                //         {
                //             strcpy(owner, owner_system);
                //         }
                //         else
                //         {
                //             return 1;
                //         }
                //     }
                //     else
                //     {
                //         return 1;
                //     }
                // }
                // else
                // {
                //     return 1;
                // }
            }

            owner = argv[++i];
        }
        else if (strcmp(argv[i], "-r") == 0)
        {
            if (show_real_length)
            {
                fprintf(stderr, "Zbyt duża ilość wystąpień argumentu '-r'! Koniec dalszego wykonywania programu i sprawdzania innych argumentów.\n");
                exit_status = 1;
                goto exit;
            }

            show_real_length = 1;
        }
        else if (strcmp(argv[i], "-f") == 0)
        {
            if (show_file_path)
            {
                fprintf(stderr, "Zbyt duża ilość wystąpień argumentu '-f'! Koniec dalszego wykonywania programu i sprawdzania innych argumentów.\n");
                exit_status = 1;
                goto exit;
            }

            show_file_path = 1;
        }
        else if (strcmp(argv[i], "-t") == 0)
        {
            if (show_exec_time)
            {
                fprintf(stderr, "Zbyt duża ilość wystąpień argumentu '-t'! Koniec dalszego wykonywania programu i sprawdzania innych argumentów.\n");
                exit_status = 1;
                goto exit;
            }

            show_exec_time = 1;
        }
        else
        {
            fprintf(stderr, "Zly argument numer %d: %s! Koniec dalszego wykonywania programu i sprawdzania innych argumentów.\n", i, argv[i]);
            exit_status = 1;
            goto exit;
        }
    }

    FILE *file = fopen(filename, "r");
    if (!file)
    {
        fprintf(stderr, "Błąd otwarcia pliku! Koniec dalszego wykonywania programu.\n");
        exit_status = 1;
        goto exit;
    }

    FILE *output_file = fopen("../wyjscie.txt", "w");
    if (!output_file)
    {
        fprintf(stderr, "Błąd otwarcia pliku wyjściowego! Koniec dalszego wykonywania programu i sprawdzania innych argumentów.\n");
        fclose(file);
        exit_status = 1;
        goto exit;
    }

    int c;
    int cc = 0;
    int page = 0;

    const char *invalid_str = "[[Nieznany znak!]]";
    const unsigned long long invalid_str_len = strlen(invalid_str);

    // 4 times more because UTF-8 is maximum 4 bytes in size
    // Allocating the maximum possible string size here
    // Reallocating each time would create overhead and be slower than this
    char *line = malloc(chars_per_page * invalid_str_len * sizeof(char));
    if (line == nullptr)
    {
        fprintf(stderr, "Błąd alokacji pamięci! Koniec dalszego wykonywania programu i sprawdzania innych argumentów.\n");
        fclose(file);
        fclose(output_file);
        exit_status = 1;
        goto exit;
    }

    if (fgetc(file) == EOF)
    {
        fprintf(stderr, "Podano pusty plik! Koniec dalszego wykonywania programu i sprawdzania innych argumentów.\n");
        free(line);
        fclose(file);
        fclose(output_file);
        exit_status = 1;
        goto exit;
    }

    int rl = 0;
    int chc = 0;
    rewind(file); // Pointer back to the beginning of file
    memset(line, '\0', chars_per_page * invalid_str_len * sizeof(char));
    while ((c = fgetc(file)) != EOF)
    {
        const int bytes = bytes_in_char(c);
        rl++;

        if (bytes == -1 || bytes > 2)
        {
            for (int k = 0; k < invalid_str_len; k++)
            {
                line[cc++] = invalid_str[k];
            }
        }
        else
        {
            int z = 0;
            char * x = malloc(bytes);

            if (x == nullptr)
            {
                fprintf(stderr, "Błąd alokacji pamięci przy sprawdzaniu multi bajtowych znaków!\n");
                exit_status = 1;
                free(line);
                fclose(file);
                fclose(output_file);
                goto exit;
            }

            line[cc++] = (char)c;
            x[z++] = (char)c;

            for (int i = 1; i < bytes; i++)
            {
                const int next_byte = fgetc(file);

                if (next_byte == EOF)
                {
                    break;
                }

                line[cc++] = (char)next_byte;
                x[z++] = (char)next_byte;
            }

            const wchar_t y = x[0] << 24 | x[1] << 16 | x[2] << 8 | x[3];
            const int bytes2 = bytes_in_char(y);

            if (bytes2 == -1 || bytes2 > 2)
            {
                for (int k = 0; k < bytes; k++)
                {
                    line[cc--] = '\0';
                }

                for (int k = 0; k < invalid_str_len; k++)
                {
                    line[cc++] = invalid_str[k];
                }
            }

            free(x);
        }

        if (++chc >= chars_per_page)
        {
            page++; cc = 0; chc = 0;
            print_header(output_file, filename, page, show_exec_time, show_file_path, show_real_length, show_date,
                         show_owner, rl, owner, start_time);
            fprintf(stdout, "%s\n\n", line);
            fprintf(output_file, "%s\n\n", line);
            memset(line, '\0', chars_per_page * invalid_str_len * sizeof(char));
        }
    }

    if (line[0] != '\0')
    {
        print_header(output_file, filename, page == 0 ? 1 : page, show_exec_time, show_file_path, show_real_length,
                     show_date, show_owner, rl, owner, start_time);
        fprintf(stdout, "%s\n", line);
        fprintf(output_file, "%s\n", line);
        memset(line, '\0', chars_per_page * invalid_str_len * sizeof(char));
    }

    free(line);
    fclose(file);
    fclose(output_file);

exit:
    printf("\n\n\n-- Naciśnij ENTER by zakończyć program --\n");
    getchar();

    return exit_status;
}
