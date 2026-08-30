#pragma once

#ifdef GETRANDLIB_EXPORTS
#define GETRANDLIB_C_API __declspec(dllexport)
#else
#define GETRANDLIB_C_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif
    /**
     * @brief Generates a random integer.
     * @return A random integer.
     */
    GETRANDLIB_C_API int getrandlib_generate_int();

    /**
     * @brief Generates a random float.
     * @return A random float.
     */
    GETRANDLIB_C_API float getrandlib_generate_float();

    /**
     * @brief Generates a random double.
     * @return A random double.
     */
    GETRANDLIB_C_API double getrandlib_generate_double();

    /**
     * @brief Generates a random integer within a specified range [min, max].
     * @param min The minimum value for the range (inclusive).
     * @param max The maximum value for the range (inclusive).
     * @return A random integer within the specified range.
     */
    GETRANDLIB_C_API int getrandlib_generate_int_range(int min, int max);

    /**
     * @brief Generates a random float within a specified range [min, max].
     * @param min The minimum value for the range.
     * @param max The maximum value for the range.
     * @return A random float within the specified range.
     */
    GETRANDLIB_C_API float getrandlib_generate_float_range(float min, float max);

    /**
     * @brief Generates a random double within a specified range [min, max].
     * @param min The minimum value for the range.
     * @param max The maximum value for the range.
     * @return A random double within the specified range.
     */
    GETRANDLIB_C_API double getrandlib_generate_double_range(double min, double max);

#ifdef __cplusplus
}
#endif
