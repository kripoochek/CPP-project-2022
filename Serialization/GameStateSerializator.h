#pragma once
#include "../States/State.h"
#include "../States/GameState.h"
#include "proto/GameState.pb.h"
#include "../Entity/Map/Map.h"
#include "Player.h"

// TODO: GameStateSerializator serialize methods can be static

struct GameStateSerializator {
    // GameStateSerializator(std::shared_ptr<GameState> gameState);
    static void deserializeMap(serialized::GameState &serializedState, std::shared_ptr<Map> gameMap, sf::Texture& verticalTexture, sf::Texture& horizontalTexture);
    static void deserializePlayers(serialized::GameState &serializedState, std::vector<std::shared_ptr<Player>> &gamePlayers, std::shared_ptr<GameTextures> gameTextures);
    static serialized::GameState serialize(std::shared_ptr<GameState> gameState);
    private:
        static void serializeMap(serialized::GameState& serializedState, std::shared_ptr<GameState> state);
        static void serializePlayers(serialized::GameState& serializedState, std::shared_ptr<GameState> state);
};