#pragma once
#include "../States/State.h"
#include "../States/GameState.h"
#include "proto/GameState.pb.h"
#include "../Entity/Map/Map.h"
#include "Player.h"

// TODO: GameStateSerializator serialize methods can be static

struct GameStateSerializator {
    GameStateSerializator(std::shared_ptr<GameState> gameState);
    void serializeMap();
    void serializePlayers();
    static void deserializeMap(serialized::GameState &serializedState, std::shared_ptr<Map> gameMap, sf::Texture& verticalTexture, sf::Texture& horizontalTexture);
    static void deserializePlayers(serialized::GameState &serializedState, std::vector<std::shared_ptr<Player>> &gamePlayers, std::shared_ptr<GameTextures> gameTextures);
    serialized::GameState serialize();
    private:
        std::shared_ptr<GameState> state;
        serialized::GameState serializedState;

};