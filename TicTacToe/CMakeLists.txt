cmake_minimum_required(VERSION 3.15)
project(TicTacToe C)

set(CMAKE_C_STANDARD 99)

add_executable(TicTacToe main.c ErrorMessages.h Feldausgabe.c Feldausgabe.h Logik.c Logik.h main.c StructDefinitions.h Netzwerk.c)