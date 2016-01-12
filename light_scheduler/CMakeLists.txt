cmake_minimum_required(VERSION 2.8)

project (light_scheduler)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")


set(CMAKE_CXX_FLAGS "-O2 -std=c++1y -Wall -pedantic")

include_directories ("${PROJECT_SOURCE_DIR}/src")
# include_directories ("/usr/local/include")
# link_directories("/usr/local/lib")

aux_source_directory(src SRC)
aux_source_directory(test TEST)

add_executable(light_scheduler_test ${TEST})
target_link_libraries(light_scheduler_test gtest pthread)

set(CMAKE_VERBOSE_MAKEFILE false)
