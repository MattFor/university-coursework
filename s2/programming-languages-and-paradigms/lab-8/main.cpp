#include <tuple>
#include <vector>
#include <memory>
#include <iostream>
#include <optional>
#include <algorithm>

constexpr int factorial(const int n)
{
    return n <= 1 ? 1 : n * factorial(n - 1);
}

int main()
{
    const auto numbers = std::make_shared<std::vector<int>>(std::initializer_list{3, 5, 2, 0, 8, 10});

    int x = -1;
    std::cout << "Podaj liczby (0 konczy): ";
    while (std::cin >> x && x != 0)
    {
        numbers->push_back(x);
    }

    int evenCount = 0, oddCount = 0;
    std::ranges::for_each(*numbers, [&](const int v)
    {
        if (v % 2 == 0)
        {
            ++evenCount;
        }
        else
        {
            ++oddCount;
        }
    });

    std::optional<int> maxValue;
    if (!numbers->empty())
    {
        maxValue = *std::ranges::max_element(*numbers);
    }

    std::vector<std::tuple<int, int>> results;
    results.reserve(numbers->size());
    for (int v : *numbers)
    {
        results.emplace_back(v, factorial(v));
    }

    std::ranges::sort(
        results,
        [](auto& a, auto& b)
        {
            return std::get<0>(a) > std::get<0>(b);
        }
    );

    std::cout << "Parzystych: " << evenCount << ", Nieparzystych: " << oddCount << "\n";

    if (maxValue)
    {
        std::cout << "Najwieksza liczba: " << *maxValue << "\n";
    }

    std::cout << "Liczba  Silnia\n";
    for (auto& [val, fact] : results)
    {
        std::cout << val << "      " << fact << "\n";
    }
}
