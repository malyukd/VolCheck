cmake_minimum_required(VERSION 3.10)
project(ServerClient CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(stream STATIC TCPstream.cpp TCPstream.h)
target_include_directories(stream PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})