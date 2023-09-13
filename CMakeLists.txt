cmake_minimum_required(VERSION 3.24)
project(Projekt)

set(CMAKE_CXX_STANDARD 17)

add_executable(Projekt SourceFiles/main.cpp SourceFiles/Cube.cpp SourceFiles/Cube.h SourceFiles/MovingCube.cpp SourceFiles/MovingCube.h SourceFiles/CubeTower.h SourceFiles/Game.cpp SourceFiles/Game.h SourceFiles/Constants.h SourceFiles/Menu.cpp SourceFiles/Menu.h )

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(C:/SFML/include)

target_link_libraries(Projekt sfml-system sfml-window sfml-graphics sfml-audio sfml-network)