cmake_minimum_required(VERSION 3.31)
project(DLL1 VERSION 1.0 LANGUAGES CXX)

# Select appropriate C++ standard based on compiler
if (MSVC)
    # MSVC supports C++26 via /std:c++latest
    add_compile_options(/std:c++latest)
    set(CMAKE_CXX_STANDARD 26)
else()
    # Use the latest widely supported GNU/Clang standard
    set(CMAKE_CXX_STANDARD 23)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ----------------------------------
# Build the SOUNDLIB shared library
# ----------------------------------
add_library(SOUNDLIB SHARED
        src/SOUNDLIB.cpp
)

target_compile_definitions(SOUNDLIB
        PRIVATE SOUNDLIBRARY_EXPORTS
)

target_include_directories(SOUNDLIB
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# ----------------------------------
# Build the executable that uses the DLL
# ----------------------------------
add_executable(DLL1
        main.cpp
)

target_link_libraries(DLL1
        PRIVATE SOUNDLIB
)

# Ensure the DLL is copied next to the executable on Windows
if (WIN32)
    add_custom_command(TARGET DLL1 POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            $<TARGET_FILE:SOUNDLIB>
            $<TARGET_FILE_DIR:DLL1>
    )
endif()