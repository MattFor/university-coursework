#include <string>
#include <vector>
#include <iostream>
#include <cstring>

bool contains(std::vector<int> w, int id)
{
    for (int i = 0; i < w.size(); i++)
    {
        if (w[i] == id)
        {
            return true;
        }
    }

    return false;
}

void zad1()
{
    // int a_freq = 0;
    // int word_count = 0;
    //
    // printf("Napisz ciąg słów.\n");
    // std::string str;
    // std::getline(std::cin, str);
    //
    // str += ' ';
    //
    // for (int i = 0; i < str.length(); i++)
    // {
    //     if (str[i] == 'a')
    //     {
    //         a_freq++;
    //     }
    //
    //     if (str[i] == ' ' && i > 0 && str[i - 1] != ' ')
    //     {
    //         word_count++;
    //     }
    // }
    //
    // printf("Litera \"a\" pojawia się: %d razy\nWystępuję %d słów.\n", a_freq, word_count);

    int a_freq = 0;
    int word_freq = 0;

    printf("Wpisz wiersz tekstu\n");
    char input[256];
    fgets(input, 255, stdin);

    strcat(input, " ");

    for (int i = 0; i < strlen(input); i++)
    {
        if (input[i] == 'a')
        {
            a_freq++;
        }

        if (i > 0 && input[i] == ' ' && input[i - 1] != ' ')
        {
            word_freq++;
        }
    }

    printf("Pojawia sie %d slow i %d znakow 'a'\n", word_freq, a_freq);
}

void zad2()
{
    // char str1[100];
    // char str2[100];
    //
    // printf("Wpisz 2 ciągi wyrazów oddzielone ENTER.\n");
    // fgets(str1, 100, stdin);
    // fgets(str2, 100, stdin);
    //
    // if (static_cast<int>(strlen(str1)) > static_cast<int>(strlen(str2)))
    // {
    //     strcpy_s(str2, str1);
    // }
    // else
    // {
    //     printf("Error encountered!\n");
    // }

    char input1[256], input2[256];

    printf("Wpisz 2 wiersze tekstu oddzielone klawiszem ENTER\n");
    fgets(input1, 255, stdin);
    fgets(input2, 255, stdin);

    if (strlen(input1) > strlen(input2))
    {
        strcpy(input1, input2);
    }
    else
    {
        printf("Error detected.\n");
    }
}

void zad3()
{
    // std::vector<std::string> input;
    //
    // for (int i = 0; i < 3; i++)
    // {
    //     input.emplace_back("");
    // }
    //
    // printf("Napisz 3 wyrazy oddzielone klawiszem ENTER.\n");
    //
    // for (int i = 0; i < 3; i++)
    // {
    //     std::getline(std::cin, input[i]);
    // }
    //
    // input[0] += ", ";
    // input[1] += ", ";
    //
    // if (input[0].length() + input[1].length() + input[2].length() > 255)
    // {
    //     printf("Error encountered!\n");
    //     return;
    // }

    char input1[256], input2[256], input3[256];

    printf("Wypisz 3 wiersze oddzielone klawiszem ENTER\n");
    fgets(input1, 255, stdin);
    fgets(input2, 255, stdin);
    fgets(input3, 255, stdin);

    input1[strcspn(input1, "\n")] = '\0';
    input2[strcspn(input2, "\n")] = '\0';
    input3[strcspn(input3, "\n")] = '\0';

    strcat(input1, ", ");
    strcat(input2, ", ");
    strcat(input1, input2);
    strcat(input1, input3);

    printf("%s\n", input1);
}

void zad4()
{
    // int special_count = 0;
    //
    // printf("Podaj ciąg słów.\n");
    // std::string input;
    // std::getline(std::cin, input);
    //
    // printf("Podaj znak specjalny do wyszukania w ciągu słów.\n");
    // std::string special;
    // std::getline(std::cin, special);
    //
    // printf("Znak występuje w indeksach: ");
    // for (int i = 0; i < input.length(); i++)
    // {
    //     if (input[i] == special[0])
    //     {
    //         printf("%d, ", i);
    //         special_count++;
    //     }
    // }
    //
    // printf("\nPojawia się %d razy.\n", special_count);

    char input1[1024];
    char input2 = ' ';

    printf("Wpisz wiersz tekstu.\n");
    fgets(input1, 1024, stdin);

    printf("Wpisz znak do wyszukania.\n");
    scanf("%c", &input2);

    int count = 0;
    for (int i = 0; i < strlen(input1); i++)
    {
        if (input1[i] == input2)
        {
            count++;
            printf("%d ", i);
        }
    }

    printf("\nZnak pojawia sie %d razy.\n", count);
}

void zad5()
{
    // printf("Podaj ciąg słów do odwrócenia.\n");
    // std::string input;
    // std::getline(std::cin, input);
    //
    // for (int i = static_cast<int>(input.length()); i >= 0; i--)
    // {
    //     printf("%c", input[i]);
    // }

    char input1[1024];
    printf("Wpisz wiersz tekstu.\n");
    fgets(input1, 1024, stdin);

    input1[strcspn(input1, "\n")] = '\0';

    for (int i = (int)strlen(input1); i >= 0; i--)
    {
        printf("%c", input1[i]);
    }

    printf("\n");
}

void zad6()
{
    // std::vector<std::string> input;
    // for (int i = 0; i < 5; i++)
    // {
    //     input.emplace_back("");
    // }
    //
    // printf("Wpisz 5 słów, po wpisaniu jednego naciśnij ENTER i wpisz kolejne.\n");
    // for (auto & i : input)
    // {
    //     std::getline(std::cin, i);
    // }
    //
    // std::vector<int> shown_ids;
    // for (int i = 0; i <= 10; i++)
    // {
    //     int shortest = 255;
    //     for (int j = 0; j < 5; j++)
    //     {
    //         if (input[j][i] - '0' < shortest && !contains(shown_ids, j))
    //         {
    //             shortest = j;
    //         }
    //     }
    //
    //     if (shortest == 255)
    //     {
    //         break;
    //     }
    //
    //     printf("%d, ", shortest);
    //
    //     shown_ids.push_back(shortest);
    //     printf("%s\n", input[shortest].c_str());
    // }

    char array[5][1024];

    printf("Wpisz 5 wierszy tekstu.\n");
    for (int i = 0; i < 5; i++)
    {
        fgets(array[i], 1024, stdin);
    }

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5 - 1 - i; j++)
        {
            if (strcmp(array[j], array[j + 1]) > 0)
            {
                char temp[1024];
                strcpy(temp, array[j]);
                strcpy(array[j], array[j + 1]);
                strcpy(array[j + 1], temp);
            }
        }
    }

    printf("Posortowane wiersze:\n");
    for (int i = 0; i < 5; i++)
    {
        printf("%d. %s", i + 1, array[i]);
    }
}

int main()
{
    // zad1();
    // zad2();
    // zad3();
    // zad4();
    // zad5();
    // zad6();
}
