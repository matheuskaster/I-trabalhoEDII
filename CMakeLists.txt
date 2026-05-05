cmake_minimum_required(VERSION 3.28)
project(I_trabalhoEDII C)

set(CMAKE_C_STANDARD 99)

include_directories(include)

file(GLOB_RECURSE SOURCES "src/*.c")

add_executable(ted ${SOURCES})
