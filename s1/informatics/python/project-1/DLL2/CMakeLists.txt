cmake_minimum_required(VERSION 3.31)
project(GET_RANDLIB VERSION 1.0 LANGUAGES CXX) # Project name for the library itself

# Set C++ standard based on compiler
if (MSVC)
    add_compile_options(/std:c++latest)
    set(CMAKE_CXX_STANDARD 20) # Using C++20
else()
    set(CMAKE_CXX_STANDARD 20) # Using C++20
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(GET_RANDLIB SHARED
        src/GET_RANDLIB.cpp
)

target_compile_definitions(GET_RANDLIB
        PRIVATE GETRANDLIB_EXPORTS
)

target_include_directories(GET_RANDLIB
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(GET_RANDLIB_Demo main.cpp)

target_link_libraries(GET_RANDLIB_Demo
        PRIVATE GET_RANDLIB
)

if (WIN32)
    add_custom_command(TARGET GET_RANDLIB_Demo POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:GET_RANDLIB>
            $<TARGET_FILE_DIR:GET_RANDLIB_Demo>
    )
endif()
