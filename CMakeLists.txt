project(app)

set( CMAKE_BUILD_TYPE Release)
#set( CMAKE_BUILD_TYPE Debug)

cmake_minimum_required(VERSION 2.8)

add_definitions(-g -DUNITY_INCLUDE_DOUBLE -DUNITY_DOUBLE_PRECISION=1e-12f -D_GNU_SOURCE)

include_directories(src)
file(GLOB INCLUDES_SRC src/*.h)
file(GLOB SOURCES "src/*.c")

if(CMAKE_BUILD_TYPE STREQUAL Debug)
    include_directories(test)
    include_directories(unity)
    file(GLOB TESTS "test/*.c")
    file(GLOB UNITY "unity/*.c")
    file(GLOB INCLUDES_UNI unity/*.h)
endif()

add_executable(app ${SOURCES} ${TESTS} ${UNITY} ${INCLUDES_SRC} ${INCLUDES_UNI})
target_link_libraries(app png m SDL2 SDL2main SDL2_ttf SDL2_image)
