cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SFML_SEARCH_PATH ${CMAKE_SOURCE_DIR}/lib/SFML)

find_library(SFML_LIBRARY SFML PATHS ${SFML_SEARCH_PATH} REQUIRED)
find_library(SFML_SYSTEM_LIBRARY sfml-system PATHS ${SFML_SEARCH_PATH} REQUIRED)
find_library(SFML_GRAPHICS_LIBRARY sfml-graphics PATHS ${SFML_SEARCH_PATH} REQUIRED)
find_library(SFML_WINDOW_LIBRARY sfml-window PATHS ${SFML_SEARCH_PATH} REQUIRED)

add_library (
    ${PROJECT_LIB_NAME}
    Condition.cpp
    Condition.h
    Action.cpp
    Action.h
    Goal.cpp
    Goal.h
    PathFinding.h
    ActionGraph.cpp
    ActionGraph.h
    SpriteAnimator.cpp
    SpriteAnimator.h
    Entity.h
    Critter.cpp
    Critter.h
    Food.cpp
    Food.h
    World.cpp
    World.h
)

target_link_libraries (
    ${PROJECT_LIB_NAME}
    ${SFML_LIBRARY}
    ${SFML_SYSTEM_LIBRARY}
    ${SFML_GRAPHICS_LIBRARY}
    ${SFML_WINDOW_LIBRARY}
)

add_executable (${PROJECT_NAME} Main.cpp)

target_link_libraries (
    ${PROJECT_NAME}
    ${PROJECT_LIB_NAME}
    ${SFML_LIBRARY}
    ${SFML_SYSTEM_LIBRARY}
    ${SFML_GRAPHICS_LIBRARY}
    ${SFML_WINDOW_LIBRARY}
)
