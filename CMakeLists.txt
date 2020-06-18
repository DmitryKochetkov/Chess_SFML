cmake_minimum_required(VERSION 3.15)
project(chess_sfml)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_MODULE_PATH /usr/share/SFML/cmake/Modules)
find_package(SFML COMPONENTS graphics audio REQUIRED)

add_executable(chess_sfml main.cpp ChessHandler.h Group.cpp Group.h Board.h Board.cpp)

target_link_libraries(chess_sfml sfml-system sfml-window sfml-graphics sfml-audio)