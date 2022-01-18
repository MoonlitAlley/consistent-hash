
SET(CMAKE_C_COMPILER "/opt/bin/gcc")
SET(CMAKE_CXX_COMPILER "/opt/bin/g++")

cmake_minimum_required(VERSION 3.5)
project(consistent_hash CXX)

set(CMAKE_CXX_STANDARD 11)

add_executable(consistent_hash main.cpp md5.cpp)