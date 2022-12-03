cmake_minimum_required(VERSION 3.23)
project(digit_recognition_cpp)

set( CMAKE_CXX_COMPILER "/usr/bin/g++" )



set(CMAKE_CXX_STANDARD 17)

add_executable(digit_recognition_cpp main.cpp headers/data.h headers/data_handler.h src/data.cpp src/data_handler.cpp KNN/headers/knn.h KNN/src/knn.cpp)
