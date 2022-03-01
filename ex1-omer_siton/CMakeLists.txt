cmake_minimum_required(VERSION 3.20)
project(ex1_omer_siton C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(ex1_omer_siton
        cipher.h
        ex1.c
        tests.c)
