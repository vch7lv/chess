cmake_minimum_required(VERSION 3.16)
project(chess_project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(
    SOURCES
    src/main.cpp
    src/Chesstypes.cpp
)

add_executable(
    chess
    ${SOURCES}
)

target_include_directories(chess PUBLIC include)

#target_link_libraries(chess sfml-system sfml-window sfml-graphics)