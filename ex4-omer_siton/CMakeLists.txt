cmake_minimum_required(VERSION 3.20)
project(ex4_omer_siton C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(ex4_omer_siton
        Hash.h
        HashSet.c
        HashSet.h
        Node.c
        Node.h
        Utils.h
        test_runner.c
        test_runner.h
        tests.c)
