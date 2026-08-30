#include <cmath>
#include <iostream>
#include <stdbool.h>

int silnia(int n)
{
    int result = 1;

    for (int i = 1; i <= n; i++)
    {
        result *= i;
    }

    return result;
}

void infloop()
{
    bool exit = false;

    while(!exit)
    {
        if (getchar() == 'e')
        {
            exit = true;
        }
    }
}

void countabc()
{
    bool exit = false;

    int cnta = 0;
    int cntb = 0;
    int cntc = 0;
    int cntelse = 0;

    while(!exit)
    {
        char input = getchar();

        switch (input)
        {
            case 'a':
                cnta++;
            break;

            case 'b':
                cntb++;
            break;

            case 'c':
                cntc++;
            break;

            case 'e':
                exit = true;
            break;

            default:
                cntelse++;
                continue;
        }
    }

    printf("Count of a: %d\nCount of b: %d\nCount of c: %d.\nCount of everything else: %d.\n", cnta, cntb, cntc, cntelse);
}

void writetofile()
{
    FILE *file = fopen("../programming.txt", "rt");

    if (file == NULL)
    {
        printf("File not found.\n");
        exit(1);
    }

    char input;
    while (fscanf(file, "%c", &input) != EOF) // !feof(file)
    {
        printf("%c", input);
    }

    fclose(file);
}

double funkcja1(double x)
{
    return 1 / (x*x + sqrt(1 + 2*x + 3 * x*x));
}

void funkcjatabelowana()
{
    double a,b,x,dx;

    scanf("%lf%lf%lf", &a, &b, &dx);

    for (x = a; x <= b; x += dx)
    {
        printf("%lf | %lf\n", x, funkcja1(x));
    }
}

int main()
{
    // printf("Silnia = %d", silnia(5));

    // infloop();

    // countabc();

    // writetofile();

    funkcjatabelowana();
}
