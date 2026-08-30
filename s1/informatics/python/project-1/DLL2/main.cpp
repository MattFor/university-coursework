//
// Created by MattFor on 23/04/2025.
//
// main.cpp - Feature demonstration for the GET_RANDLIB

#include <iostream> // For console output (std::cout)
#include "GET_RANDLIB.hpp" // Include the C++ header for the library
#include "GET_RANDLIB_C.h" // Include the C header for the C API

int main()
{
    std::cout << "--- GET_RANDLIB Feature Demonstration ---" << std::endl;
    std::cout << std::endl;

    std::cout << "--- C++ API ---" << std::endl;

    const int random_int_cpp = GETRANDLIB::generate_random<int>();
    std::cout << "Random int (full range): " << random_int_cpp << std::endl;

    const auto random_float_cpp = GETRANDLIB::generate_random<float>();
    std::cout << "Random float (full range): " << random_float_cpp << std::endl;

    const auto random_double_cpp = GETRANDLIB::generate_random<double>();
    std::cout << "Random double (full range): " << random_double_cpp << std::endl;

    std::cout << std::endl;

    constexpr int min_int              = 10;
    constexpr int max_int              = 100;
    const int     random_int_range_cpp = GETRANDLIB::generate_random_range<int>(min_int, max_int);
    std::cout << "Random int [" << min_int << ", " << max_int << "]: " << random_int_range_cpp << std::endl;

    constexpr float min_float              = -50.5f;
    constexpr float max_float              = 50.5f;
    const auto      random_float_range_cpp = GETRANDLIB::generate_random_range<float>(min_float, max_float);
    std::cout << "Random float [" << min_float << ", " << max_float << "]: " << random_float_range_cpp << std::endl;

    constexpr double min_double              = 1000.0;
    constexpr double max_double              = 2000.0;
    const auto       random_double_range_cpp = GETRANDLIB::generate_random_range<double>(min_double, max_double);
    std::cout << "Random double [" << min_double << ", " << max_double << "]: " << random_double_range_cpp << std::endl;

    std::cout << std::endl;

    std::cout << "--- C API ---" << std::endl;

    const int random_int_c = getrandlib_generate_int();
    std::cout << "Random int (C API): " << random_int_c << std::endl;

    const float random_float_c = getrandlib_generate_float();
    std::cout << "Random float (C API): " << random_float_c << std::endl;

    const double random_double_c = getrandlib_generate_double();
    std::cout << "Random double (C API): " << random_double_c << std::endl;

    std::cout << std::endl;

    constexpr int c_min_int          = -20;
    constexpr int c_max_int          = 5;
    const auto    random_int_range_c = getrandlib_generate_int_range(c_min_int, c_max_int);
    std::cout << "Random int [" << c_min_int << ", " << c_max_int << "] (C API): " << random_int_range_c << std::endl;

    constexpr float c_min_float          = 0.0f;
    constexpr float c_max_float          = 1.0f;
    const auto      random_float_range_c = getrandlib_generate_float_range(c_min_float, c_max_float);
    std::cout << "Random float [" << c_min_float << ", " << c_max_float << "] (C API): " << random_float_range_c <<
            std::endl;

    constexpr double c_min_double          = -100.0;
    constexpr double c_max_double          = 0.0;
    const auto       random_double_range_c = getrandlib_generate_double_range(c_min_double, c_max_double);
    std::cout << "Random double [" << c_min_double << ", " << c_max_double << "] (C API): " << random_double_range_c <<
            std::endl;


    std::cout << std::endl;
    std::cout << "--- Demonstration Complete ---" << std::endl;
}
