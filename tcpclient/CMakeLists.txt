cmake_minimum_required(VERSION 2.8)
project(tcpclient)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

set(SOURCE_LIB TCPClient.cpp)

add_library(tcpclient STATIC ${SOURCE_LIB})
