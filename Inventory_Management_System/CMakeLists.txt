cmake_minimum_required(VERSION 4.2)
project(Inventory_Management_System C)

set(CMAKE_C_STANDARD 11)

add_executable(Inventory_Management_System main.c
        inventory.h
        inventory.c)
