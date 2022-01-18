cmake_minimum_required(VERSION 3.20)
project(cppProject)

set(CMAKE_CXX_STANDARD 23)

add_executable(cppProject main.cpp v0.1/Student.cpp v0.1/Student.h v0.2/SortedStudent.cpp v0.2/SortedStudent.h)
