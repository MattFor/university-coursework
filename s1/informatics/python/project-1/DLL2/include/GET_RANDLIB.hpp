//
// Created by MattFor on 23/04/2025.
//
// Transformed from GETINPUTLIBRARY to GET_RANDLIB

#pragma once

#include <random>

#ifdef GETRANDLIB_EXPORTS
#define GETRANDLIB_API __declspec(dllexport)
#else
#define GETRANDLIB_API __declspec(dllimport)
#endif

namespace GETRANDLIB
{
    extern std::random_device rd;
    extern std::mt19937       engine;

    // --- C++ API for Random Number Generation ---

    /**
     * @brief Generates a random number of type T within its full representable range.
     * @tparam T The type of the random number to generate (e.g., int, float, double).
     * @return A random value of type T.
     */
    template <typename T>
    GETRANDLIB_API T generate_random();

    /**
     * @brief Generates a random number of type T within the specified range [min, max].
     * @tparam T The type of the random number to generate (e.g., int, float, double).
     * @param min The minimum value for the range (inclusive).
     * @param max The maximum value for the range (inclusive for integral types, potentially exclusive for floating-point depending on distribution).
     * @return A random value of type T within the specified range.
     */
    template <typename T>
    GETRANDLIB_API T generate_random_range(T min, T max);
}
