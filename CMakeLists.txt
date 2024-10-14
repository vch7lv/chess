cmake_minimum_required(VERSION 3.16)
project(chess_project)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(
    SOURCES
    src/main.cpp
    src/Chesstypes.cpp
    src/LocalGame.cpp 
    src/Player.cpp 
    src/GameException.cpp
    src/ChessBoard.cpp
)

add_executable(
    chess
    ${SOURCES}
)

target_include_directories(chess PUBLIC include)
target_include_directories(chess PUBLIC widgets/include)

add_subdirectory(widgets)

target_link_libraries(chess widgets)

#target_link_libraries(chess sfml-system sfml-window sfml-graphics)