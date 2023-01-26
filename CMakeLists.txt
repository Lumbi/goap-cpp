cmake_minimum_required(VERSION 3.25)

project(goap)

set(PROJECT_LIB_NAME ${PROJECT_NAME}_Lib)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src)

include(CTest)
add_subdirectory(test)

enable_testing()
