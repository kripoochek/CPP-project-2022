cmake_minimum_required(VERSION 3.21)
project(my_tanks_in_labirint)

set(CMAKE_CXX_STANDARD 17)

include_directories(Entity States Config Button Entity/Components Entity/Map/Map Entity/Map Bullet)
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)

add_executable(my_tanks_in_labirint Bullet/Bullet.cpp main.cpp Game.cpp Game.h
        States/State.cpp States/State.h States/GameState.cpp States/GameState.h
        Entity/Entity.cpp Entity/Entity.h
        States/MainMenuState.cpp States/MainMenuState.h
        Button/Button.cpp Button/Button.h Entity/Player.cpp Entity/Player.h
        Entity/Components/MovementComponent.cpp Entity/Components/MovementComponent
        Entity/Map/Wall.cpp Entity/Map/Box.cpp
        )

target_link_libraries(my_tanks_in_labirint sfml-graphics sfml-audio)
