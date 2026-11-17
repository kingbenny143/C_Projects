cmake_minimum_required(VERSION 4.2)
project(Employee_Payroll_Management_System C)

set(CMAKE_C_STANDARD 11)

add_executable(Employee_Payroll_Management_System main.c
        employee.h
        employee.c)
