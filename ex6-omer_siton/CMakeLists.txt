cmake_minimum_required(VERSION 3.20)
project(ex6_omer_siton)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ex6_omer_siton
        Apartment.cpp
        Apartment.h
        AVL.cpp
        AVL.h
        Find.h
        MesureTimeHelper.h

        Stack.cpp
        Stack.h
        test_runner.h
        test_runner.cpp
        tests.cpp
        )
