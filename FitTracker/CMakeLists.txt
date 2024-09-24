cmake_minimum_required(VERSION 3.29)
project(FitTracker)

set(CMAKE_CXX_STANDARD 20)

add_executable(FitTracker main.cpp sqlite/sqlite3.h sqlite/sqlite3.c)
