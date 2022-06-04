cmake_minimum_required(VERSION 3.21)
project(my_tanks_in_labirint)

set(CMAKE_CXX_STANDARD 17)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
find_package(Box2D COMPONENTS collision common dynamics rope REQUIRED)
find_package(Threads)

include_directories(Entity States Config Button Entity/Components Entity/Map Bullet CollisionManager Server Serialization)

add_executable(my_tanks_in_labirint Bullet/Bullet.cpp main.cpp Game.cpp
        States/State.cpp States/State.h States/RoundState.cpp States/GameState.cpp
        States/RoundClientState.h States/RoundClientState.cpp
        States/RoundHostState.h States/RoundHostState.cpp
        Server/NetworkClient.h Server/NetworkClient.cpp
        Server/NetworkServer.h Server/NetworkServer.cpp
        Serialization/GameStateSerializator.h Serialization/GameStateSerializator.cpp
        Serialization/proto/GameState.pb.cc
        Entity/Entity.cpp Entity/Entity.h
        States/MainMenuState.cpp States/MainMenuState.h
        Button/Button.cpp Button/Button.h Entity/Player.cpp Entity/Player.h
        Entity/Components/MovementComponent.cpp Entity/Components/MovementComponent
        Entity/Map/Wall.cpp Entity/Map/Box.cpp Entity/Map/Map.cpp Utils.cpp
        States/GameTextures.h States/GameTextures.cpp Entity/Components/HitboxComponent.cpp Entity/Components/HitboxComponent.h
        CollisionManager/CollisionManager.cpp
        )

target_link_libraries(my_tanks_in_labirint sfml-graphics sfml-audio Box2D)
target_link_libraries(my_tanks_in_labirint protobuf)
target_link_libraries(my_tanks_in_labirint Threads::Threads)