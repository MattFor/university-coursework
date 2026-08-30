//
// Created by MattFor on 23/04/2025.
//
// Implementation file for the GET_RANDLIB

#include <random>
#include <limits>
#include <algorithm>

#include "GET_RANDLIB.hpp"

namespace GETRANDLIB
{
    std::random_device rd;
    std::mt19937       engine(rd());
}

template <>
GETRANDLIB_API int GETRANDLIB::generate_random<int>()
{
    std::uniform_int_distribution<int> dist(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
    return dist(GETRANDLIB::engine);
}

template <>
GETRANDLIB_API float GETRANDLIB::generate_random<float>()
{
    std::uniform_real_distribution<float> dist(std::numeric_limits<float>::lowest(), std::numeric_limits<float>::max());
    return dist(GETRANDLIB::engine);
}

template <>
GETRANDLIB_API double GETRANDLIB::generate_random<double>()
{
    std::uniform_real_distribution<double> dist(std::numeric_limits<double>::lowest(),
                                                std::numeric_limits<double>::max());
    return dist(GETRANDLIB::engine);
}

template <>
GETRANDLIB_API int GETRANDLIB::generate_random_range<int>(int min, int max)
{
    if (min > max)
    {
        std::swap(min, max);
    }

    std::uniform_int_distribution dist(min, max);
    return dist(GETRANDLIB::engine);
}

template <>
GETRANDLIB_API float GETRANDLIB::generate_random_range<float>(float min, float max)
{
    if (min > max)
    {
        std::swap(min, max);
    }

    std::uniform_real_distribution dist(min, max);
    return dist(GETRANDLIB::engine);
}

template <>
GETRANDLIB_API double GETRANDLIB::generate_random_range<double>(double min, double max)
{
    if (min > max)
    {
        std::swap(min, max);
    }

    std::uniform_real_distribution dist(min, max);
    return dist(GETRANDLIB::engine);
}

#include "GET_RANDLIB_C.h"

GETRANDLIB_API int getrandlib_generate_int()
{
    return GETRANDLIB::generate_random<int>();
}

GETRANDLIB_API float getrandlib_generate_float()
{
    return GETRANDLIB::generate_random<float>();
}

GETRANDLIB_API double getrandlib_generate_double()
{
    return GETRANDLIB::generate_random<double>();
}

GETRANDLIB_API int getrandlib_generate_int_range(int min, int max)
{
    return GETRANDLIB::generate_random_range<int>(min, max);
}

GETRANDLIB_API float getrandlib_generate_float_range(float min, float max)
{
    return GETRANDLIB::generate_random_range<float>(min, max);
}

GETRANDLIB_API double getrandlib_generate_double_range(double min, double max)
{
    return GETRANDLIB::generate_random_range<double>(min, max);
}
