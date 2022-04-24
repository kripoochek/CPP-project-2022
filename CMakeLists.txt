cmake_minimum_required(VERSION 3.21)
project(my_tanks_in_labirint)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
find_package(Box2D COMPONENTS collision common dynamics rope REQUIRED)

include_directories(Entity States Config Button Entity/Components Entity/Map Bullet CollisionManager)

add_executable(my_tanks_in_labirint Bullet/Bullet.cpp main.cpp Game.cpp
        States/State.cpp States/State.h States/GameState.cpp 
        Entity/Entity.cpp Entity/Entity.h
        States/MainMenuState.cpp States/MainMenuState.h
        Button/Button.cpp Button/Button.h Entity/Player.cpp Entity/Player.h
        Entity/Components/MovementComponent.cpp Entity/Components/MovementComponent
        Entity/Map/Wall.cpp Entity/Map/Box.cpp Entity/Map/Map.cpp Entity/Map/Utils.cpp
        States/GameTextures.h States/GameTextures.cpp Entity/Components/HitboxComponent.cpp Entity/Components/HitboxComponent.h
        CollisionManager/CollisionManager.cpp
        )

target_link_libraries(my_tanks_in_labirint sfml-graphics sfml-audio Box2D)
