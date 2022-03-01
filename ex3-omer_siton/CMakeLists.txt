cmake_minimum_required(VERSION 3.20)
project(ex3_omer_siton C)

set(CMAKE_C_FLAGS "-Wextra -Werror -Wall -Wvla -std=c99")

include_directories(.)

add_executable(ex3_omer_siton
        ex3.c
        ex3.h
        main.c)
