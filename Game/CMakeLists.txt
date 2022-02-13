cmake_minimum_required(VERSION 3.21)
project(Game)

set(CMAKE_CXX_STANDARD 17)
include_directories(Controller Objects Map theme GameMap)
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(Game main.cpp Objects/Tank.cpp Controller/Controller.cpp Objects/DynamicObject.cpp theme/simple_theme.cpp Map/utils.cpp Map/map_box.cpp Map/map.cpp GameMap/GameMap.cpp )

target_link_libraries(Game sfml-graphics sfml-audio)
