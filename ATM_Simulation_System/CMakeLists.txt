cmake_minimum_required(VERSION 4.3)
project(ATM_Simulation_System C)

set(CMAKE_C_STANDARD 11)

add_executable(ATM_Simulation_System main.c
        atm.h
        account.h
        transaction.h
        account.c
        transaction.c
        atm.c
)
