cmake_minimum_required(VERSION 3.20)
project(ex5_omer_siton)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ex5_omer_siton
        Activation.cpp
        Activation.h
        Dense.cpp
        Dense.h
        main.cpp
        Matrix.cpp
        Matrix.h
        MlpNetwork.cpp
        MlpNetwork.h)
