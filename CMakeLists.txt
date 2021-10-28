cmake_minimum_required(VERSION 3.8)
project(BigInteger)

set(CMAKE_CXX_STANDARD 20)

set(SOURCE_FILES main.cpp biginteger.h)
add_executable(BigInteger ${SOURCE_FILES})