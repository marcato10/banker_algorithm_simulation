cmake_minimum_required(VERSION 3.25)
project(Banker C)

set(CMAKE_C_STANDARD 17)

add_executable(Banker main.c Array.h Process.h Queue.h)
