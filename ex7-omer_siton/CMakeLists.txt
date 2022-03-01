project(ex7_omer_siton)
cmake_minimum_required(VERSION 3.20)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ex7_omer_siton
        vl_vector.h
        helpers.h
        test_runner.cpp
        test_runner.h
        tests.cpp)
