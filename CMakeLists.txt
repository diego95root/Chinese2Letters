project(tests)

#set( CMAKE_BUILD_TYPE Release)
#set( CMAKE_BUILD_TYPE Debug)

cmake_minimum_required(VERSION 2.8)

set(CMAKE_BUILD_TYPE "NoTest")

add_definitions(-DUNITY_INCLUDE_DOUBLE -DUNITY_DOUBLE_PRECISION=1e-12f -D_GNU_SOURCE)

include_directories(src)
file(GLOB INCLUDES_SRC src/*.h)

if(CMAKE_BUILD_TYPE STREQUAL Debug)
    include_directories(test)
    include_directories(include)
    file(GLOB TESTS "test/*.c")
    file(GLOB UNITY "include/*.c")
    file(GLOB INCLUDES_UNI include/*.h)
    file(GLOB SOURCES "src/*.c")
elseif(CMAKE_BUILD_TYPE STREQUAL NoTest)
    file(GLOB SOURCES "src/*.c")
else() 
  message(FATAL_ERROR "I don't know the CMAKE_BUILD_TYPE you gave me!")
endif()

add_executable(tests ${SOURCES} ${TESTS} ${UNITY} ${INCLUDES_SRC} ${INCLUDES_UNI})
target_link_libraries(tests png m SDL2 SDL2main SDL2_image)