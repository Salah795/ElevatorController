cmake_minimum_required(VERSION 4.2)
project(ElevatorController)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(ElevatorController
        Elevator.cpp
        Elevator.h
        Hardware.cpp
        Hardware.h
        Floor.cpp
        Floor.h)
