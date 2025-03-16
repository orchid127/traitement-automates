cmake_minimum_required(VERSION 3.27)
project(traitement_automates C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(traitement_automates
        Automate.h
        Automate.c
        main.c)
