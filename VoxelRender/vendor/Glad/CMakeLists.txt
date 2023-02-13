cmake_minimum_required(VERSION 3.21)
project(Glad)

set(CMAKE_CXX_STANDARD 14)

include_directories(include)

add_library(Glad
    include/GLAD/glad.h
    include/KHR/khrplatform.h
    src/glad.c)
