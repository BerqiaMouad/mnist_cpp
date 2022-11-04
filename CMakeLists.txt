cmake_minimum_required(VERSION 3.23)
project(digit_recognition_cpp)

set(CMAKE_CXX_STANDARD 17)

add_executable(digit_recognition_cpp main.cpp data.h data_handler.h data.cpp data_handler.cpp)
