cmake_minimum_required(VERSION 4.2)
project(Library_Management_System C)

set(CMAKE_C_STANDARD 11)

add_executable(Library_Management_System main.c
        library.h
        library.c)
