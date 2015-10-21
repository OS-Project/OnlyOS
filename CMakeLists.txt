cmake_minimum_required(VERSION 3.3)
project(OnlyOS)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp drivers/gpio/driver_gpio.c drivers/gpio/driver_gpio.h utils/errno.c utils/errno.h)
add_executable(OnlyOS ${SOURCE_FILES})