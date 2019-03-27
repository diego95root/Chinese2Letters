project(tests)

#set( CMAKE_BUILD_TYPE Release)
set( CMAKE_BUILD_TYPE Debug)

cmake_minimum_required(VERSION 2.8)

include_directories(src)

set(CMAKE_BUILD_TYPE "test")

if(CMAKE_BUILD_TYPE STREQUAL test)
    include_directories(test)
    file(GLOB TESTS "test/*.c")
    file(GLOB SOURCES "src/*.c")
elseif(CMAKE_BUILD_TYPE STREQUAL release)
    file(GLOB SOURCES "src/*.c")
else() 
  message(FATAL_ERROR "I don't know the CMAKE_BUILD_TYPE you gave me!")
endif()

add_executable(tests ${SOURCES} ${TESTS})