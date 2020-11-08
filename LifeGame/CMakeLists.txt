cmake_minimum_required(VERSION 3.17)
project(LifeGame)

set(CMAKE_CXX_STANDARD 20)

add_executable(LifeGame main.cpp InputHandler.cpp InputHandler.h Field.cpp Field.h GameLogic.cpp GameLogic.h LifeGame.cpp LifeGame.h)