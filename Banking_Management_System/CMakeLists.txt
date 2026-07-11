cmake_minimum_required(VERSION 4.2)
project(Banking_Management_System C)

set(CMAKE_C_STANDARD 11)

add_executable(Banking_Management_System main.c
        bank.h
        bank.c)
