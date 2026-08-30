cmake_minimum_required(VERSION 3.30)
project(Proj1 LANGUAGES CXX)

if (MSVC)
    add_compile_options(/std:c++latest)
    set(CMAKE_CXX_STANDARD 26)
else ()
    set(CMAKE_CXX_STANDARD 23)
endif ()
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SDL3_DIR "C:/SDL3/cmake")
set(CMAKE_PREFIX_PATH "${SDL3_DIR}")
find_package(SDL3 REQUIRED)
find_package(OpenGL REQUIRED)

include_directories(
        "C:/glfw-3.4.bin.WIN64/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/algorithms"
        "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui"
        "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/backends"
        "C:/SDL3/i686-w64-mingw32/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/DLL1/include"
        "${CMAKE_CURRENT_SOURCE_DIR}/DLL2/include"
)

link_directories(
        "C:/glfw-3.4.bin.WIN64/lib-mingw-w64"
        "C:/SDL3/x86_64-w64-mingw32/lib"
)

file(GLOB_RECURSE SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/algorithms/*.cpp"
)

file(GLOB IMGUI_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_glfw.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/backends/imgui_impl_opengl3.cpp"
)

add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui"
        "${CMAKE_CURRENT_SOURCE_DIR}/vendor/imgui/backends"
)

set(SOUNDLIB_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/DLL1/cmake-build-debug")
find_library(
        SOUNDLIB_IMPORT_LIB
        NAMES libSOUNDLIB.dll.a SOUNDLIB
        PATHS "${SOUNDLIB_BUILD_DIR}"
        NO_DEFAULT_PATH
)
if (NOT SOUNDLIB_IMPORT_LIB)
    message(FATAL_ERROR "Cannot find libSOUNDLIB.dll.a in ${SOUNDLIB_BUILD_DIR}")
endif ()

cmake_minimum_required(VERSION 3.31)
project(Proj1 VERSION 1.0 LANGUAGES CXX)

if (MSVC)
    add_compile_options(/std:c++latest)
    set(CMAKE_CXX_STANDARD 20)
else()
    set(CMAKE_CXX_STANDARD 20)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(GET_RANDLIB_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/DLL2/cmake-build-debug")

find_library(
        GET_RANDLIB_IMPORT_LIB
        NAMES libGET_RANDLIB.dll.a GET_RANDLIB
        PATHS "${GET_RANDLIB_BUILD_DIR}"
        NO_DEFAULT_PATH
)

if (NOT GET_RANDLIB_IMPORT_LIB)
    message(FATAL_ERROR "Cannot find libGET_RANDLIB.dll.a or GET_RANDLIB import library in ${GET_RANDLIB_BUILD_DIR}. Ensure GET_RANDLIB is built.")
endif ()

set(SOUNDLIB_BUILD_DIR "${CMAKE_CURRENT_SOURCE_DIR}/DLL1/cmake-build-debug")

find_library(
        SOUNDLIB_IMPORT_LIB
        NAMES libSOUNDLIB.dll.a SOUNDLIB
        PATHS "${SOUNDLIB_BUILD_DIR}"
        NO_DEFAULT_PATH
)

if (NOT SOUNDLIB_IMPORT_LIB)
    message(FATAL_ERROR "Cannot find libSOUNDLIB.dll.a or SOUNDLIB import library in ${SOUNDLIB_BUILD_DIR}. Ensure SOUNDLIB is built.")
endif ()

add_executable(Proj1
        main.cpp
        ${SOURCES}
)

target_link_libraries(Proj1
        PRIVATE
         ${OPENGL_LIBRARIES}
         SDL3::SDL3
         glfw3
        ${SOUNDLIB_IMPORT_LIB}
        ${GET_RANDLIB_IMPORT_LIB}
        winmm
         imgui
         sdl3
)

if (WIN32)
    add_custom_command(TARGET Proj1 POST_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${SOUNDLIB_BUILD_DIR}/libSOUNDLIB.dll"
            $<TARGET_FILE_DIR:Proj1>
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "${GET_RANDLIB_BUILD_DIR}/libGET_RANDLIB.dll"
            $<TARGET_FILE_DIR:Proj1>
            COMMAND ${CMAKE_COMMAND} -E copy_if_different
            "C:/SDL3/x86_64-w64-mingw32/bin/SDL3.dll"
            $<TARGET_FILE_DIR:Proj1>
    )
endif()
