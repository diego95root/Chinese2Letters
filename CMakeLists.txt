project(tests)

#set( CMAKE_BUILD_TYPE Release)
set( CMAKE_BUILD_TYPE Debug)

cmake_minimum_required(VERSION 2.8)

include_directories(src)

file(GLOB SOURCES "src/*.c")

add_executable(tests ${SOURCES})