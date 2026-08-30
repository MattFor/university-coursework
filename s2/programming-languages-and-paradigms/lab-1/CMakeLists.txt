cmake_minimum_required(VERSION 3.30)
project(JiPP_S2)

set(CMAKE_CXX_STANDARD 26)

add_executable(JiPP_S2 main.cpp
        headers/Employee.h
        headers/Manager.h
        headers/Intern.h
        src/Employee.cpp
        src/Intern.cpp
        src/Manager.cpp)
