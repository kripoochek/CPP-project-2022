#pragma once
#include "../States/State.h"
#include "../States/GameState.h"
#include "proto/GameState.pb.h"
#include "../Entity/Map/Map.h"
#include "Player.h"
#include "Bullet.h"

struct GameStateSerializator {
    static void deserializeMap(serialized::GameState &serializedState, std::shared_ptr<Map> gameMap, sf::Texture& verticalTexture, sf::Texture& horizontalTexture);
    static void deserializePlayers(serialized::GameState &serializedState, std::vector<std::shared_ptr<Player>> &gamePlayers, std::shared_ptr<GameTextures> gameTextures);
    // some bug with bullets array, when receiving, so note a actual number of bullets
    static void deserializeBullets(serialized::GameState &serializedState, std::deque<std::pair<int, std::shared_ptr<Bullet>>> &gameBullets, sf::Texture& bulletTexture, int bulletsNumber);

    static serialized::GameState serialize(std::shared_ptr<GameState> gameState);
    private:
        static void serializeMap(serialized::GameState& serializedState, std::shared_ptr<GameState> state);
        static void serializePlayers(serialized::GameState& serializedState, std::shared_ptr<GameState> state);
        static void serializeBullets(serialized::GameState& serializedState, std::shared_ptr<GameState> state);
};