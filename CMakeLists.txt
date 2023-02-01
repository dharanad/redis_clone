cmake_minimum_required(VERSION 3.24)
project(redis_clone CXX)

set(CMAKE_CXX_STANDARD 17)

add_executable(redis_clone main.cpp server.cpp server.h protocol.cpp protocol.h utils.cpp utils.h utils.h el.cpp el.h consts.h conn.cpp conn.h)
