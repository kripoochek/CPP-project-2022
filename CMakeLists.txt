cmake_minimum_required(VERSION 3.21)
project(my_tanks_in_labirint)

set(CMAKE_CXX_STANDARD 17)
set(THREADS_PREFER_PTHREAD_FLAG ON)

find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)
find_package(Box2D COMPONENTS collision common dynamics rope REQUIRED)
find_package(Threads)

include_directories(Entity States Config Button Entity/Components Entity/Map Bullet CollisionManager Server Serialization)

add_executable(my_tanks_in_labirint Bullet/Bullet.cpp main.cpp Game.cpp
        Serialization/proto/GameState.pb.cc Serialization/GameStateSerializator.cpp
        Server/NetworkClient.cpp Server/NetworkClient.h
        Server/NetworkServer.cpp Server/NetworkServer.h
        States/GameClientState.cpp States/GameClientState.h
        States/State.cpp States/State.h States/GameState.cpp 
        Entity/Entity.cpp Entity/Entity.h
        States/MainMenuState.cpp States/MainMenuState.h
        States/GameHostState.cpp States/GameHostState.h
        Button/Button.cpp Button/Button.h Entity/Player.cpp Entity/Player.h
        Entity/Components/MovementComponent.cpp Entity/Components/MovementComponent
        Entity/Map/Wall.cpp Entity/Map/Box.cpp Entity/Map/Map.cpp Entity/Map/Utils.cpp
        States/GameTextures.h States/GameTextures.cpp Entity/Components/HitboxComponent.cpp Entity/Components/HitboxComponent.h
        CollisionManager/CollisionManager.cpp
        )

# add_executable(my_tanks_in_labirint_server Bullet/Bullet.cpp Server/server.cpp Game.cpp
#         Serialization/proto/GameState.pb.cc Serialization/GameStateSerializator.cpp
#         Server/NetworkClient.cpp Server/NetworkClient.h
#         States/GameClientState.cpp States/GameClientState.h
#         States/State.cpp States/State.h States/GameState.cpp 
#         Entity/Entity.cpp Entity/Entity.h
#         States/MainMenuState.cpp States/MainMenuState.h
#         Button/Button.cpp Button/Button.h Entity/Player.cpp Entity/Player.h
#         Entity/Components/MovementComponent.cpp Entity/Components/MovementComponent
#         Entity/Map/Wall.cpp Entity/Map/Box.cpp Entity/Map/Map.cpp Entity/Map/Utils.cpp
#         States/GameTextures.h States/GameTextures.cpp Entity/Components/HitboxComponent.cpp Entity/Components/HitboxComponent.h
#         CollisionManager/CollisionManager.cpp
# )

target_link_libraries(my_tanks_in_labirint sfml-graphics sfml-audio Box2D)
target_link_libraries(my_tanks_in_labirint protobuf)
target_link_libraries(my_tanks_in_labirint Threads::Threads)

# target_link_libraries(my_tanks_in_labirint_server sfml-graphics sfml-audio Box2D)
# target_link_libraries(my_tanks_in_labirint_server protobuf)
# target_link_libraries(my_tanks_in_labirint_server Threads::Threads)

