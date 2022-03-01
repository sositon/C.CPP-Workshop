cmake_minimum_required(VERSION 3.20)
project(ex2_omer_siton C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(ex2_omer_siton
        ex2.c
        ex2.h
        test_ex2.c
        )
