cmake_minimum_required(VERSION 3.15)
project(chess_sfml)

set(CMAKE_CXX_STANDARD 17)

file(READ sfml_path.txt CMAKE_MODULE_PATH)
file(READ sfml_path.txt SFML_DIR)
find_package(SFML COMPONENTS graphics audio REQUIRED)

add_executable(chess_sfml main.cpp ChessHandler.h Group.cpp Group.h ResourceHolder.h ResourceHolder.cpp Button.cpp Button.h Label.cpp Label.h IListener.cpp IListener.h)

target_link_libraries(chess_sfml sfml-system sfml-window sfml-graphics sfml-audio)