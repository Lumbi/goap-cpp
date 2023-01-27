cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_library (
    ${PROJECT_LIB_NAME}
    Condition.cpp
    Condition.h
    Action.cpp
    Action.h
    Goal.cpp
    Goal.h
    ActionPath.cpp
    ActionPath.h
    ActionGraph.cpp
    ActionGraph.h
)

add_executable (${PROJECT_NAME} Main.cpp)

target_link_libraries (${PROJECT_NAME} ${PROJECT_LIB_NAME})
