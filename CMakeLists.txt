cmake_minimum_required(VERSION 3.24)
project(redis_clone C)

set(CMAKE_C_STANDARD 17)

add_executable(redis_clone main.c server.c server.h)
