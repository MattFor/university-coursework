#include <time.h>
#include <stdio.h>
#include <stdlib.h>

// Recursively count how many times digit k occurs in number x
int ile(int x, const int k)
{
    if (x < 0)
    {
        x = -x;
    }

    if (x == 0)
    {
        return (k == 0) ? 1 : 0;
    }

    // Count in current digit and add count in the rest
    return ((x % 10) == k ? 1 : 0) + ile(x / 10, k);
}

// Recursively count occurrences of digit k in an array of n integers
int zlicz1(const int n, int *a, const int k)
{
    if (n <= 0)
    {
        return 0;
    }

    return ile(a[0], k) + zlicz1(n - 1, a + 1, k);
}

// Recursively compute the sum of digits of x
int suma_cyfr(int x)
{
    if (x < 0)
    {
        x = -x;
    }

    if (x < 10)
    {
        return x;
    }

    return (x % 10) + suma_cyfr(x / 10);
}

// Recursively find the maximum digit sum among all n elements in array a
int zlicz2(const int n, int *a)
{
    if (n == 1)
    {
        return suma_cyfr(a[0]);
    }

    const int current_sum = suma_cyfr(a[0]);
    const int max_rest = zlicz2(n - 1, a + 1);

    return (current_sum > max_rest) ? current_sum : max_rest;
}

// Helper function for zlicz3 to find the index of the element with maximum digit sum
int zlicz3_helper(const int n, int *a, const int current_index, int best_index, int best_sum) {
    if (n == 0)
    {
        return best_index;
    }

    const int current_sum = suma_cyfr(a[0]);
    if (current_sum > best_sum)
    {
        best_sum = current_sum;
        best_index = current_index;
    }

    return zlicz3_helper(n - 1, a + 1, current_index + 1, best_index, best_sum);
}

// Recursively find the index of the element with maximum digit sum
int zlicz3(const int n, int *a)
{
    if (n <= 0)
    {
        return -1;
    }

    return zlicz3_helper(n, a, 0, 0, suma_cyfr(a[0]));
}

int main()
{
    srand(time(0));

    int n = 0;
    int k = 0;

    printf("Enter the number of elements: ");
    if (scanf("%d", &n) != 1 || n <= 0)
    {
        printf("Invalid number of elements.\n");
        return 1;
    }

    // Allocate an array of n integers.
    int *a = malloc(n * sizeof(int));
    if (!a)
    {
        printf("Memory allocation error.\n");
        return 1;
    }

    for (int i = 0; i < n; i++)
    {
        a[i] = rand() % (n * 100);

        if (rand() % 2)
        {
            a[i] = -a[i];
        }
    }

    printf("Array elements:\n");
    for (int i = 0; i < n; i++)
    {
        printf("%d, ", a[i]);
    }
    printf("\n");

    printf("Enter the digit to count (0-9): ");
    if (scanf("%d", &k) != 1 || k < 0 || k > 9)
    {
        printf("Invalid digit.\n");
        free(a);
        return 1;
    }

    const int total_occurrences = zlicz1(n, a, k);
    printf("Total occurrences of digit %d: %d\n", k, total_occurrences);

    const int max_digit_sum = zlicz2(n, a);
    printf("Maximum digit sum among array elements: %d\n", max_digit_sum);

    const int index_max = zlicz3(n, a);
    if (index_max != -1)
    {
        printf("Index of element with maximum digit sum: %d\n", index_max);
        printf("Element: %d (digit sum = %d)\n", a[index_max], suma_cyfr(a[index_max]));
    }
    else
    {
        printf("Array is empty, cannot determine maximum digit sum index.\n");
    }

    free(a);
}