cmake_minimum_required(VERSION 4.2)
project(Contact_Book C)

set(CMAKE_C_STANDARD 11)

add_executable(Contact_Book main.c
        contact.c
        contact.h)
