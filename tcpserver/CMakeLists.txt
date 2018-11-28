cmake_minimum_required(VERSION 2.8)
project(tcpserver)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")

set(SOURCE_LIB TCPServer.cpp Util.cpp)

add_library(tcpserver STATIC ${SOURCE_LIB})
