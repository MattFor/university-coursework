//
// Created by MattFor on 31.03.2025.
//

#define USE_WHITE 0

#include <ctime>
#include <random>
#include <string>
#include <utility>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <functional>
#include <type_traits>
#include <GLFW/glfw3.h>
#include <unordered_map>

#include "../algorithms/sorting_algorithms.h"

typedef int (*GetRandIntFn)();
typedef float (*GetRandFloatFn)();
typedef double (*GetRandDoubleFn)();
typedef int (*GetRandIntRangeFn)(int min, int max);
typedef float (*GetRandFloatRangeFn)(float min, float max);
typedef double (*GetRandDoubleRangeFn)(double min, double max);

bool randomLibLoaded = false;

enum class VALUE_TYPE : int
{
    FLOAT,
    INTEGER
};

enum class PERFORMANCE_MODE : int
{
    MIXED,
    NEGATIVES,
    POSITIVES,

    SORTED,
    REVERSED
};

enum class MODE : int
{
    IDLE,
    SORTING,
    SETTINGS,
    COMPLETED,
    RANDOMIZING
};

enum class ALGORITHM : int
{
    BUBBLE = 1,
    INSERTION,
    SELECTION,
    QUICKSORT,
    SHELL,
    HEAP,
    RADIX,
    COCKTAIL,
    BOGO, TIMSORT,
    GNOMESORT,
    SPREADSORT
};

struct Settings
{
    bool automatic;

    int sound;
    int numValues;
    int windowWidth;
    int windowHeight;

    float barWidth;
    float delaySeconds;

    std::string multipleTests;
    std::string performanceMeasurement;
};

// Create a template so wse can exchange ALGORITHM enum values with ints
template <>
struct std::hash<ALGORITHM>
{
    size_t operator ()(const ALGORITHM& algorithm) const noexcept
    {
        return std::hash<int>()(static_cast<int>(algorithm));
    }
};

// Define a function pointer type for our sort step functions
using SortingAlgorithm = std::function<bool(std::vector<Value>&, int&, int&, int)>;

// Define a structure to hold both the sort function and its custom delay
struct SortConfig
{
    // Order has to be like that to look nicer
    SortingAlgorithm func;
    float            delay;

    // Inline default constructor
    SortConfig() : func(nullptr), delay(0.0f)
    {
    }

    // Convenience constructor
    SortConfig(SortingAlgorithm f, const float x) : func(std::move(f)), delay(x)
    {
    }
};

// Example initialisation of the algorithm configuration map
std::unordered_map<ALGORITHM, SortConfig> algoConfig{
    {ALGORITHM::BOGO, SortConfig{bogo_sort_step, 0.00001f}},
    {ALGORITHM::BUBBLE, SortConfig{bubble_sort_step, 0.0001f}},
    {ALGORITHM::COCKTAIL, SortConfig{cocktail_sort_step, 0.00092f}},
    {ALGORITHM::GNOMESORT, SortConfig{gnome_sort_step, 0.0001f}},
    {ALGORITHM::HEAP, SortConfig{heap_sort_step, 0.008f}},
    {ALGORITHM::INSERTION, SortConfig{insertion_sort_step, 0.01f}},
    {
        ALGORITHM::SELECTION, SortConfig{
            selection_sort_step,
            0.00001f
        }
    },
    {ALGORITHM::SHELL, SortConfig{shell_sort_step, 0.001f}},
    {
        ALGORITHM::TIMSORT, SortConfig{
            timsort_step,
            0.5f
        }
    }, // SUPER FAST
    {
        ALGORITHM::RADIX, SortConfig{
            radix_lsd_bucket_sort_step,
            1.5f
        }
    },
    {ALGORITHM::QUICKSORT, SortConfig{quicksort_step, 0.01f}},
    {
        ALGORITHM::SPREADSORT, SortConfig{
            spreadsort_step,
            0.0f
        }
    } // TODO: FIX - experimental
};

// Create a wrapper function so that we can use the previously created hashmap to assign all functions when needed
std::function<bool(std::vector<Value>&, int&, int&, int)>
make_sorting_function(const SortingAlgorithm& sortingAlgorithm, int& arrayAccesses, int& comparisons,
                      float /*configDelay*/)
{
    return [sortingAlgorithm, &arrayAccesses, &comparisons](std::vector<Value>& values, int& _a, int& _b,
                                                            const int           delayArg) -> bool
    {
        static bool firstCall = true;

        if (firstCall)
        {
            firstCall = false;
            return false;
        }

        return sortingAlgorithm(values, arrayAccesses, comparisons, delayArg);
    };
}

template <typename T>
bool call_input_impl(HMODULE lib, const char* prompt, T& value, const T& default_value)
{
    using DispatcherFn = bool (*)(const char*, const char*, void*, const void*);

    static auto get_input_dispatch = reinterpret_cast<DispatcherFn>(
        GetProcAddress(lib, "get_input_dispatch"));

    if (!get_input_dispatch)
    {
        OutputDebugStringA("Failed to load get_input_dispatch from DLL\n");
        return false;
    }

    const char* type = nullptr;

    if constexpr (std::is_same_v<T, int>)
    {
        type = "int";
    }
    else if constexpr (std::is_same_v<T, float>)
    {
        type = "float";
    }
    else if constexpr (std::is_same_v<T, double>)
    {
        type = "double";
    }
    else if constexpr (std::is_same_v<T, const char*> || std::is_same_v<T, char*> ||
                       std::is_same_v<T, std::string>)
    {
        type = "string";
    }
    else
    {
        OutputDebugStringA("Unsupported type for get_input\n");
        return false;
    }

    return get_input_dispatch(type, prompt, &value, &default_value);
}

template <typename T>
bool call_input(HMODULE lib, const char* prompt, T& value, const T& default_value)
{
    return call_input_impl(lib, prompt, value, default_value);
}

// --- Helper to attempt setting value from default ---
// Tries direct assignment first, then stream conversion. Returns true on success.
template <typename T, typename U>
bool try_set_value_from_default(T& value, const U& default_value)
{
    // Attempt 1: Direct Assignment (if types allow)
    // Use 'if constexpr' (C++17) to check assignability at compile time
    if constexpr (std::is_assignable_v<T&, const U&>)
    {
        value = default_value;
        return true; // Assignment successful
    }
    // Attempt 2: Stream Conversion (if direct assignment fails or isn't possible)
    else
    {
        std::ostringstream oss;
        if (!(oss << default_value))
        {
            std::cerr << "\nError: Cannot convert default value of its type to a string representation." << std::endl;
            return false;
        }

        std::istringstream iss(oss.str());
        if (iss >> value)
        {
            if (char dummy; !(iss >> dummy))
            {
                return true;
            }

            std::cerr << "\nWarning: Default value '" << oss.str() <<
                    "' parsed into type T, but had trailing characters." << std::endl;
            return true;
        }

        std::cerr << "\nError: Cannot parse the string representation ('" << oss.str() <<
                "') of the default value into the required value type." << std::endl;
        return false;
    }
}


template <typename T, typename U>
void get_input(const std::string& prompt, T& value, const U& default_value)
{
    std::cout << prompt;
    std::string input_str;

    if (!std::getline(std::cin, input_str))
    {
        std::cerr << "\nWarning: Input stream failed. Attempting to use default value." << std::endl;
        if (!try_set_value_from_default(value, default_value))
        {
            std::cerr << "\nCritical Error: Input stream failed AND could not use default value." << std::endl;
        }
        std::cin.clear();
        return;
    }

    if (input_str.empty())
    {
        if (!try_set_value_from_default(value, default_value))
        {
            std::cerr << "\nError: Failed to apply default value." << std::endl;
        }
    }
    else
    {
        std::istringstream iss_input(input_str);
        if (!(iss_input >> value))
        {
            std::cerr << "\nWarning: Could not parse input '" << input_str << "'. Attempting to use default value." <<
                    std::endl;
            if (!try_set_value_from_default(value, default_value))
            {
                std::cerr << "\nError: Could not apply default value after input parse failure." << std::endl;
            }
        }
        else
        {
            if (char dummy; iss_input >> dummy)
            {
                std::cerr << "\nWarning: Extra characters detected after parsing input '" << input_str <<
                        "'. Using parsed value anyway." << std::endl;
            }
        }
    }
}

template <typename T, typename U>
void get_input(const char* prompt, T& value, const U& default_value)
{
    get_input(std::string(prompt), value, default_value);
}

std::function<bool(std::vector<Value>&, int&, int&, int)>
read_settings(Settings& settings, std::vector<Value>& values, float& max, const bool repeating, int& arrayAccesses,
              int&      comparisons)
{
    comparisons   = 0;
    arrayAccesses = 0;

    if (!repeating)
    {
        get_input("Do you want to start in performance measurement mode? (y/n | default: n):\n",
                  settings.performanceMeasurement, "n");

        // If we are stepping into performance measurement, we won't be needing any GUI,
        // we can get what we need and exit
        if (settings.performanceMeasurement == "y" || settings.performanceMeasurement == "Y")
        {
            get_input("Do you want to run multi-size analysis? (y/n | default: n):\n",
                      settings.multipleTests, "n");

            if (settings.multipleTests != "y" && settings.multipleTests != "Y")
            {
                get_input("Enter the number of values to sort (default: 100):\n", settings.numValues, 100);
            }

            constexpr auto algorithm = ALGORITHM::BUBBLE;
            const auto&    config    = algoConfig[algorithm];
            return make_sorting_function(config.func, arrayAccesses, comparisons, config.delay);
        }

        get_input("Enter the number of values to sort (default: 100):\n", settings.numValues, 100);

        get_input("Enter window width (default: auto-adjust):\n", settings.windowWidth, -1);
        get_input("Enter window height (default: 480):\n", settings.windowHeight, 480);

        std::string temp_sound;
        get_input("Do you want to have sound? (y/n | default: n):\n", temp_sound, "n");

        settings.sound = temp_sound == "y" || temp_sound == "Y" ? 1 : -10000000;
    }

    if (settings.sound == 0)
    {
        settings.sound = -100;
    }

    // Automatic window width calculation based on number of values
    constexpr int defaultBarWidth = 10;
    if (settings.windowWidth <= 0)
    {
        const int autoWidth  = settings.numValues * defaultBarWidth;
        settings.windowWidth = (autoWidth > 1920) ? 1920 : autoWidth;
        settings.barWidth    = static_cast<float>(settings.windowWidth) / static_cast<float>(settings.numValues);
    }
    else
    {
        const float possibleBarWidth =
                static_cast<float>(settings.windowWidth) / static_cast<float>(settings.numValues);
        settings.barWidth = (possibleBarWidth < defaultBarWidth) ? possibleBarWidth : defaultBarWidth;
    }

    std::string temp_auto_sorting;
    get_input("Do you want to enable auto sorting? (y/n | default: y):\n", temp_auto_sorting, "y");

    settings.automatic = temp_auto_sorting == "y" || temp_auto_sorting == "Y";

    if (settings.automatic)
    {
        get_input("Enter delay between steps (default: automatic - for best viewing experience):\n",
                  settings.delaySeconds, -1);
    }
    else
    {
        settings.delaySeconds = 0.0;
    }

    if (!repeating)
    {
        values.clear();
        for (int i = 0; i < settings.numValues; i++)
        {
            int randomValue = 10 + std::rand() % (settings.windowHeight - 10);

            if (static_cast<float>(randomValue) > max)
            {
                max = static_cast<float>(randomValue);
            }

            float xPos = static_cast<float>(i) * settings.barWidth;
            values.emplace_back(randomValue, xPos);
        }
    }

    std::cout << "Choose a sorting algorithm:\n";
    std::cout << "1  - Bubble Sort\t\t\tSlow\n";
    std::cout << "2  - Insertion Sort\t\t\tFast\n";
    std::cout << "3  - Selection Sort\t\t\tFast\n";
    std::cout << "4  - Quicksort\t\t\t\tFast\n";
    std::cout << "5  - Shell Sort\t\t\t\tAverage\n";
    std::cout << "6  - Heap Sort\t\t\t\tTurbo\n";
    std::cout << "7  - Radix LSD Bucket Sort\t\tTurbo\n";
    std::cout << "8  - Cocktail Sort\t\t\tModerate\n";
    std::cout << "9  - Bogo Sort\t\t\t\tNever ending\n";
    std::cout << "10 - Timsort (Simplified)\t\tTurbo\n";
    std::cout << "11 - Gnome Sort\t\t\t\tAverage\n";
    std::cout << "12 - Spreadsort (Simplified)\t\tTurbo\n";

    int choice = 0;
    get_input("", choice, -1); // Default to Bubble Sort

    auto algorithm = static_cast<ALGORITHM>(choice);

    if (!algoConfig.contains(algorithm))
    {
        std::cout << "Invalid choice. Defaulting to Bubble Sort.\n";
        algorithm = ALGORITHM::BUBBLE;
    }

    auto [function, delay] = algoConfig[algorithm];

    if (settings.delaySeconds == -1)
    {
        settings.delaySeconds = delay;
    }

    std::cout << "Using ";
    switch (algorithm)
    {
        case ALGORITHM::BUBBLE:
            std::cout << "Bubble Sort.\n";
            break;
        case ALGORITHM::INSERTION:
            std::cout << "Insertion Sort.\n";
            break;
        case ALGORITHM::SELECTION:
            std::cout << "Selection Sort.\n";
            break;
        case ALGORITHM::QUICKSORT:
            std::cout << "Quicksort.\n";
            break;
        case ALGORITHM::SHELL:
            std::cout << "Shell Sort.\n";
            break;
        case ALGORITHM::HEAP:
            std::cout << "Heap Sort.\n";
            break;
        case ALGORITHM::RADIX:
            std::cout << "Radix LSD Bucket Sort.\n";
            break;
        case ALGORITHM::COCKTAIL:
            std::cout << "Cocktail Sort.\n";
            break;
        case ALGORITHM::BOGO:
            std::cout << "Bogo Sort.\n";
            break;
        case ALGORITHM::TIMSORT:
            std::cout << "Timsort (Simplified).\n";
            break;
        case ALGORITHM::GNOMESORT:
            std::cout << "Gnome Sort.\n";
            break;
        case ALGORITHM::SPREADSORT:
            std::cout << "Spreadsort (Simplified).\n";
            break;
        default:
            std::cout << "Bubble Sort.\n";
            break;
    }

    // Use the wrapper to get what we want
    return make_sorting_function(function, arrayAccesses, comparisons, delay);
}

std::vector<Value> generate_values(const PERFORMANCE_MODE& testType, const int numValues, const int windowHeight,
                                   const VALUE_TYPE        valueType)
{
    std::vector<Value> vals;
    vals.reserve(numValues);

    HMODULE h_getrandlib = LoadLibraryA("libGET_RANDLIB.dll");
    if (!h_getrandlib)
    {
        std::cerr << "Failed to load GET_RANDLIB.dll. Ensure it's built and in the executable path.\n";
    }

    if (!randomLibLoaded)
    {
        std::cout << "GET_RANDLIB.dll loaded successfully." << '\n';
    }

    // Get function pointers for the C API functions
    auto getrandlib_generate_int_ptr = reinterpret_cast<GetRandIntFn>(
           GetProcAddress(h_getrandlib, "getrandlib_generate_int")
    );

    auto getrandlib_generate_float_ptr = reinterpret_cast<GetRandFloatFn>(
           GetProcAddress(h_getrandlib, "getrandlib_generate_float")
    );

    auto getrandlib_generate_double_ptr = reinterpret_cast<GetRandDoubleFn>(
           GetProcAddress(h_getrandlib, "getrandlib_generate_double")
    );

    auto getrandlib_generate_int_range_ptr = reinterpret_cast<GetRandIntRangeFn>(
           GetProcAddress(h_getrandlib, "getrandlib_generate_int_range")
    );

    auto getrandlib_generate_float_range_ptr = reinterpret_cast<GetRandFloatRangeFn>(
           GetProcAddress(h_getrandlib, "getrandlib_generate_float_range")
    );

    auto getrandlib_generate_double_range_ptr = reinterpret_cast<GetRandDoubleRangeFn>(
           GetProcAddress(h_getrandlib, "getrandlib_generate_double_range")
    );

    // Check if all function pointers were obtained successfully
    if (!getrandlib_generate_int_ptr || !getrandlib_generate_float_ptr || !getrandlib_generate_double_ptr ||
        !getrandlib_generate_int_range_ptr || !getrandlib_generate_float_range_ptr || !getrandlib_generate_double_range_ptr)
    {
        std::cerr << "Failed to get one or more function pointers from GET_RANDLIB.dll.\n";
        FreeLibrary(h_getrandlib); // Clean up the loaded library
    }

    if (!randomLibLoaded)
    {
        std::cout << "Successfully loaded custom random lib." << '\n';
        std::cout << std::endl;
        randomLibLoaded = true;
    }

    switch (testType)
    {
        case PERFORMANCE_MODE::POSITIVES:
        {
            for (int i = 0; i < numValues; i++)
            {
                if (valueType == VALUE_TYPE::INTEGER)
                {
                    // Use the loaded function pointer
                    int val = std::abs(getrandlib_generate_int_ptr());
                    vals.emplace_back(val, 0.0f);
                }
                else // FLOAT
                {
                    // Use the loaded function pointer
                    float val = std::abs(getrandlib_generate_float_ptr());
                    vals.emplace_back(val, 0); // Use int dummy for float constructor
                }
            }
        }
        break;

        case PERFORMANCE_MODE::NEGATIVES:
        {
            for (int i = 0; i < numValues; i++)
            {
                if (valueType == VALUE_TYPE::INTEGER)
                {
                    // Use the loaded function pointer
                    int val = getrandlib_generate_int_ptr();

                    if (val > 0)
                    {
                        val = -val;
                    }

                    vals.emplace_back(val, 0.0f);
                }
                else // FLOAT
                {
                    // Use the loaded function pointer
                    float val = getrandlib_generate_float_ptr();

                    if (val > 0)
                    {
                        val = -val;
                    }

                    vals.emplace_back(val, 0); // Use int dummy for float constructor
                }
            }
        }
        break;

        case PERFORMANCE_MODE::MIXED:
        {
            for (int i = 0; i < numValues; i++)
            {
                if (valueType == VALUE_TYPE::INTEGER)
                {
                    // Use the loaded function pointer
                    int val = getrandlib_generate_int_ptr();
                    vals.emplace_back(val, 0.0f);
                }
                else // FLOAT
                {
                    // Use the loaded function pointer
                    float val = getrandlib_generate_float_ptr();
                    vals.emplace_back(val, 0); // Use int dummy for float constructor
                }
            }
        }
        break;

        case PERFORMANCE_MODE::SORTED:
        {
            // This case generates sorted/reversed values, not random ones,
            // so the random library is not used here.
            if (valueType == VALUE_TYPE::INTEGER)
            {
                for (int i = 0; i < numValues; i++)
                {
                    int val = 10 + i * ((windowHeight - 10) / numValues);
                    vals.emplace_back(val, 0.0f);
                }
            }
            else // FLOAT
            {
                for (int i = 0; i < numValues; i++)
                {
                    float val = 10.0f + static_cast<float>(i) *
                                (static_cast<float>(windowHeight - 10) / static_cast<float>(numValues));
                    vals.emplace_back(val, 0); // Use int dummy for float constructor
                }
            }

            std::reverse(vals.begin(), vals.end());
        }
        break;

        case PERFORMANCE_MODE::REVERSED:
        {
            // This case generates sorted/reversed values, not random ones,
            // so the random library is not used here.
            for (int i = 0; i < numValues; i++)
            {
                if (valueType == VALUE_TYPE::INTEGER)
                {
                    int val = 10 + i * ((windowHeight - 10) / numValues);
                    vals.emplace_back(val, 0.0f);
                }
                else // FLOAT
                {
                    float val = 10.0f + static_cast<float>(i) *
                                (static_cast<float>(windowHeight - 10) / static_cast<float>(numValues));
                    vals.emplace_back(val, 0); // Use int dummy for float constructor
                }
            }
        }
        break;

        default:
        {
            // Do nothing, vals remains empty
        }
    }

    return vals;
}

// In case the user resized the window, we need to adjust the width of our bars
void framebuffer_size_callback(GLFWwindow* window, const int width, const int height)
{
    auto* settings         = static_cast<Settings*>(glfwGetWindowUserPointer(window));
    settings->windowWidth  = width;
    settings->windowHeight = height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, 0, height, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

// Update the bars if the width has been changed
void update_bar_positions(std::vector<Value>& values, const int windowWidth)
{
    const float barWidth = static_cast<float>(windowWidth) / static_cast<float>(values.size());
    for (size_t i = 0; i < values.size(); i++)
    {
        values[i].setX(i * barWidth);
    }
}

void draw_values(const std::vector<Value>& values, const float       barWidth, const float windowHeight,
                 const float               maximum_value, const MODE mode, const int       step, const int sound)
{
    int i = 0;
    for (const auto& v : values)
    {
        if (mode == MODE::COMPLETED)
        {
            if (i == step)
            {
                glColor3f(1.0f, 0.0f, 1.0f); // Magenta (Purple)
                playTone(values[step].getValue(), 40 + sound);
            }
            else if (i < step)
            {
                glColor3f(0.0f, 1.0f, 0.0f); // Green
                playTone(values[step].getValue(), 40 + sound);
            }
            else
            {
                glColor3f(1.0f, 1.0f, 1.0f); // White
            }
        }
        else if (mode == MODE::IDLE)
        {
            glColor3f(0.2f, 0.7f, 1.0f);
        }
        else if (mode == MODE::SORTING)
        {
#ifdef USE_WHITE
            glColor3f(1.0f, 1.0f, 1.0f); // White
#else
			glColor3f(0.2f, 0.7f, 1.0f); // Light blue
#endif
        }
        else if (mode == MODE::RANDOMIZING)
        {
            glColor3f(1.0f, 0.0, 0.0); // Red
        }
        else
        {
            // Default color: white
            glColor3f(1.0f, 1.0f, 1.0f);
        }

        const float x      = v.getX();
        const float height = (v.getValue() / maximum_value) * 0.8f * windowHeight;

        // Draw triangles since it's faster than quads
        glBegin(GL_TRIANGLES);
        glVertex2f(x, 0.0);
        glVertex2f(x + barWidth, 0.0);
        glVertex2f(x + barWidth, height);

        glVertex2f(x, 0.0);
        glVertex2f(x + barWidth, height);
        glVertex2f(x, height);
        glEnd();

        i++;
    }
}

void execute_logic(std::vector<Value>& values,
                   const std::function<bool(std::vector<Value>&, int&, int&, int)>& sortingStep, MODE& mode,
                   bool& sorted, int& arrayAccesses, int& comparisons, const int duration_ms)
{
    if (sorted)
    {
        if (mode != MODE::IDLE && mode != MODE::SETTINGS)
        {
            mode = MODE::COMPLETED;
        }

        return;
    }

    sorted = sortingStep(values, arrayAccesses, comparisons, duration_ms);
}

void print_values(const std::vector<Value>& values)
{
    std::cout << "Current values: ";
    for (const auto& v : values)
    {
        std::cout << v.getValue() << " ";
    }

    std::cout << "\n";
}
