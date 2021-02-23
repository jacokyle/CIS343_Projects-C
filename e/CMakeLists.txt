cmake_minimum_required(VERSION 3.17)
project(Project_1 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(Project_1
        CuTest.c
        CuTest.h
        driver.c
        othello.c
        othello.h
        tests.c)
