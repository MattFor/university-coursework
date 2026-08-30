#include <stdio.h>
#include <stdlib.h>
#include <tgmath.h>

int z5(int n)
{
    int result = 1;

    for (int i = 1; i <= n; i++)
    {
        result *= i;
    }

    return result;
}

void z7()
{
    while(1)
    {
        if (getchar() == 'e')
        {
            break;
        }
    }
}

void z8()
{
    int cnta = 0;
    int cntb = 0;
    int cntc = 0;
    int cntelse = 0;

    while(1)
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
            goto exit;
            break;

        case '\n':
            break;

        default:
            cntelse++;
            continue;
        }
    }

exit:
    printf("Count of a: %d\nCount of b: %d\nCount of c: %d.\nCount of everything else: %d.\n", cnta, cntb, cntc, cntelse);
}

void z9()
{
    int cnta = 0;
    int cntb = 0;
    int cntc = 0;
    int cntelse = 0;

    while(1)
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
            goto cntc;
            break;

        case 'e':
            goto exit;
            break;

        case '\n':
            break;

        default:
        cntc:
            cntelse++;
            continue;
        }
    }

    exit:
        printf("Count of a: %d\nCount of b: %d\nCount of c: %d.\nCount of everything else: %d.\n", cnta, cntb, cntc, cntelse);
}

void z13()
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

// Dla zad15
double ff(double x)
{
    return 1.0 / (x*x + sqrt(1.0 + 2*x + 3*x*x));
}

void z15()
{
    double a, b, x, dx;

    scanf("%lf%lf%lf", &a, &b, &dx);

    FILE *file = fopen("../result.txt", "wt");

    if (file == NULL)
    {
        printf("File not found.\n");
        exit(1);
    }

    for (x = a; x <= b; x += dx)
    {
        double y = ff(x);

        fprintf(file, "\t%10.2lf\t\t%15.4lf\n", x, y);
        printf("\t%10.2lf\t\t%15.4lf\n", x, y);
    }

    fclose(file);
}


int main()
{
    // printf("%d", z5(5));
    // z7();
    // z8();
    // z9();
    // z13();
    // z15();
}
