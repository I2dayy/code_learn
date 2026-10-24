cmake_minimum_required(VERSION 3.27)
project(DynamicArray C)

set(CMAKE_C_STANDARD 99)

file(GLOB SOURCES "*.c")

add_executable(${PROJECT_NAME} ${SOURCES})
