cmake_minimum_required(VERSION 3.22)
project(uwu_mode)

set(CMAKE_CXX_STANDARD 20)

set(GCC_FLAGS "-static")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${GCC_FLAGS}")

add_executable(${PROJECT_NAME} main.cpp src/myKeyboardProcHook.cpp headers/myKeyboardProcHook.h)
