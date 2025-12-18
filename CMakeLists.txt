cmake_minimum_required(VERSION 4.1)
project(.)

set(CMAKE_CXX_STANDARD 20)

add_executable(MineSweeper
        utils/Cell.h
        utils/Board.h
        utils/Game.h
        utils/GameConsole.h
        main.cpp
        main.cpp
)
