CMAKE_MINIMUM_REQUIRED(VERSION 3.16)

project(lab2)

set(CMAKE_CXX_STANDARD 17)


add_executable(lab2 main.cpp
        sorter/sorter.tpp
        sorter/sorter.h
        Sequence/Sequence.h
        tests/tests.h
        tests/tests.cpp
        "tests/perfomance_tests.cpp")