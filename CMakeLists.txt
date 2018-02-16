cmake_minimum_required(VERSION 3.9)
project(Tetris2_0)

set(CMAKE_CXX_STANDARD 11)

add_executable(Tetris2_0 main.cpp Tetromino.cpp Tetromino.h Constants.h Shape.h Shape.cpp ShapeManager.cpp ShapeManager.h shapes.h shapes.cpp Game.cpp Game.h)

set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake_modules")
find_package(SFML REQUIRED system window graphics network audio)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(Tetris2_0 ${SFML_LIBRARIES})
endif()