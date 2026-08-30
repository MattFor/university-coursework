//
// Created by MattFor on 12/03/2025.
//

#include <cmath>
#include <vector>
#include <random>
#include <chrono>
#include <iostream>
#include <algorithm>

/**
 * Oglny opis algorytmu (hitoria, dzialanie, typy algorytmu, dlaczego, kto)
 * Opisac graficznie
 * opis implementacji
 * ( jak kod zostal podzielony, zrealizowany )
 * (opis struktur danych, nazwy )
 * docstrings do obu funkcji - jaki typ docstringow zostal wybrany
 * - DO PYTHONA
 * opis i roznice pomiedzy strukturami danych w c++ / pythonie
 */


void radixSortInt(std::vector<long long>& arr)
{
    if (arr.empty())
    {
        return;
    }

    const long long maxVal = *std::ranges::max_element(arr);

    for (long long exp = 1; maxVal / exp > 0; exp *= 10)
    {
        std::vector<std::vector<long long>> buckets(10);

        for (long long num : arr)
        {
            const long long digit = (num / exp) % 10;
            buckets[digit].push_back(num);
        }

        long long index = 0;
        for (long long d = 0; d < 10; d++)
        {
            for (const long long num : buckets[d])
            {
                arr[index++] = num;
            }
        }
    }
}

std::vector<double> radixSortFloats(const std::vector<double>& arr, const int precision = 6)
{
    const double factor = pow(10, precision);
    std::vector<double> negatives, positives;

    // Separate the numbers.
    for (double x : arr)
    {
        if (x < 0)
        {
            negatives.push_back(x);
        }
        else
        {
            positives.push_back(x);
        }
    }

    // Convert floats to integers.
    std::vector<long long> posInt, negInt;
    for (const double x : positives)
    {
        posInt.push_back(static_cast<long long>(round(x * factor)));
    }

    for (const double x : negatives)
    {
        negInt.push_back(static_cast<long long>(round(-x * factor)));
    }

    radixSortInt(posInt);
    radixSortInt(negInt);

    // Back to doubles.
    std::vector<double> sortedPos, sortedNeg;
    for (const long long num : posInt)
    {
        sortedPos.push_back(num / factor);
    }

    for (const long long num : negInt)
    {
        sortedNeg.push_back(- (num / factor));
    }

    std::ranges::reverse(sortedNeg);

    std::vector<double> sortedArr;
    sortedArr.insert(sortedArr.end(), sortedNeg.begin(), sortedNeg.end());
    sortedArr.insert(sortedArr.end(), sortedPos.begin(), sortedPos.end());

    return sortedArr;
}

/**
 * Using long long everywhere instead of ints in order
 * to avoid overflows during conversions
 */
int main()
{
    constexpr long long n = 2000000;
    std::vector<double> arr(n);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dis(-1000.0, 1000.0);

    for (long long i = 0; i < n; i++)
    {
        arr[i] = dis(gen);
    }

    std::cout << "First 20 elements before sorting:" << '\n';
    for (long long i = 0; i < 20 && i < arr.size(); i++)
    {
        std::cout << arr[i] << " ";
    }
    std::cout << '\n';

    const auto start = std::chrono::high_resolution_clock::now();
    const std::vector<double> sortedArr = radixSortFloats(arr, 6);
    const auto end = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double> diff = end - start;

    std::cout << "First 20 elements after sorting:" << '\n';
    for (long long i = 0; i < 20 && i < sortedArr.size(); i++)
    {
        std::cout << sortedArr[i] << " ";
    }
    std::cout << '\n';
    std::cout << "Radix sort execution time: " << diff.count() << " seconds" << '\n';

    // Default std::sort comparison
    std::vector<double> arrCopy = arr;
    const auto startStd = std::chrono::high_resolution_clock::now();
    std::ranges::sort(arrCopy);
    const auto endStd = std::chrono::high_resolution_clock::now();
    const std::chrono::duration<double> diffStd = endStd - startStd;

    std::cout << "First 20 elements after default std::sort:" << '\n';
    for (long long i = 0; i < 20 && i < arrCopy.size(); i++)
    {
        std::cout << arrCopy[i] << " ";
    }

    std::cout << '\n';
    std::cout << "Default std::sort execution time: " << diffStd.count() << " seconds" << '\n';
}


// //
// // Created by MattFor on 12/03/2025.
// //
//
// #include <cmath>
// #include <vector>
// #include <random>
// #include <chrono>
// #include <iostream>
// #include <algorithm>
//
// /**
//  * Oglny opis algorytmu (hitoria, dzialanie, typy algorytmu, dlaczego, kto)
//  * Opisac graficznie
//  * opis implementacji
//  * ( jak kod zostal podzielony, zrealizowany )
//  * (opis struktur danych, nazwy )
//  * docstrings do obu funkcji - jaki typ docstringow zostal wybrany
//  * - DO PYTHONA
//  * opis i roznice pomiedzy strukturami danych w c++ / pythonie
//  * statystyki ->  zapytac sie na AiSD
//  */
//
//
// void radixSortInt(std::vector<long>& arr)
// {
//     if (arr.empty())
//     {
//         return;
//     }
//
//     const long maxVal = *std::ranges::max_element(arr);
//
//     for (long exp = 1; maxVal / exp > 0; exp *= 10)
//     {
//         std::vector<std::vector<long>> buckets(10);
//
//         for (long num : arr)
//         {
//             const long digit = (num / exp) % 10;
//             buckets[digit].push_back(num);
//         }
//
//         long index = 0;
//         for (long d = 0; d < 10; d++)
//         {
//             for (const long num : buckets[d])
//             {
//                 arr[index++] = num;
//             }
//         }
//     }
// }
//
// std::vector<double> radixSortFloats(const std::vector<double>& arr, const int precision = 6)
// {
//     const double factor = pow(10, precision);
//     std::vector<double> negatives, positives;
//
//     // Separate the numbers.
//     for (double x : arr)
//     {
//         if (x < 0)
//         {
//             negatives.push_back(x);
//         }
//         else
//         {
//             positives.push_back(x);
//         }
//     }
//
//     // Convert floats to integers.
//     std::vector<long> posInt, negInt;
//     for (const double x : positives)
//     {
//         posInt.push_back(static_cast<long>(round(x * factor)));
//     }
//
//     for (const double x : negatives)
//     {
//         negInt.push_back(static_cast<long>(round(-x * factor)));
//     }
//
//     radixSortInt(posInt);
//     radixSortInt(negInt);
//
//     // Back to doubles.
//     std::vector<double> sortedPos, sortedNeg;
//     for (const long num : posInt)
//     {
//         sortedPos.push_back(num / factor);
//     }
//
//     for (const long num : negInt)
//     {
//         sortedNeg.push_back(- (num / factor));
//     }
//
//     std::ranges::reverse(sortedNeg);
//
//     std::vector<double> sortedArr;
//     sortedArr.insert(sortedArr.end(), sortedNeg.begin(), sortedNeg.end());
//     sortedArr.insert(sortedArr.end(), sortedPos.begin(), sortedPos.end());
//
//     return sortedArr;
// }
//
// /**
//  * Using long everywhere instead of ints in order
//  * to avoid overflows during conversions
//  */
// int main()
// {
//     constexpr long n = 4000000;
//     std::vector<double> arr(n);
//
//     std::random_device rd;
//     std::mt19937 gen(rd());
//     std::uniform_real_distribution<double> dis(-1000.0, 1000.0);
//
//     for (long i = 0; i < n; i++)
//     {
//         arr[i] = dis(gen);
//     }
//
//     std::cout << "First 20 elements before sorting:" << '\n';
//     for (long i = 0; i < 20 && i < arr.size(); i++)
//     {
//         std::cout << arr[i] << " ";
//     }
//     std::cout << '\n';
//
//     const auto start = std::chrono::high_resolution_clock::now();
//     const std::vector<double> sortedArr = radixSortFloats(arr, 6);
//     const auto end = std::chrono::high_resolution_clock::now();
//     const std::chrono::duration<double> diff = end - start;
//
//     std::cout << "First 20 elements after sorting:" << '\n';
//     for (long i = 0; i < 20 && i < sortedArr.size(); i++)
//     {
//         std::cout << sortedArr[i] << " ";
//     }
//     std::cout << '\n';
//     std::cout << "Radix sort execution time: " << diff.count() << " seconds" << '\n';
//
//     // Default std::sort comparison
//     std::vector<double> arrCopy = arr;
//     const auto startStd = std::chrono::high_resolution_clock::now();
//     std::ranges::sort(arrCopy);
//     const auto endStd = std::chrono::high_resolution_clock::now();
//     const std::chrono::duration<double> diffStd = endStd - startStd;
//
//     std::cout << "First 20 elements after default std::sort:" << '\n';
//     for (long i = 0; i < 20 && i < arrCopy.size(); i++)
//     {
//         std::cout << arrCopy[i] << " ";
//     }
//
//     std::cout << '\n';
//     std::cout << "Default std::sort execution time: " << diffStd.count() << " seconds" << '\n';
// }
