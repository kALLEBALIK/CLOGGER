cmake_minimum_required(VERSION 3.17)
project(CLOGGER C)

set(CMAKE_C_STANDARD 99)

add_executable(CLOGGER WIN32 "src/main.c" "src/key.h" "src/data.h" "src/common.h")