#pragma once
#include "../States/State.h"
#include "../States/GameState.h"
#include "proto/GameState.pb.h"

struct GameStateSerializator {
    GameStateSerializator(std::shared_ptr<GameState> state);
    void serializeMap();
    void serializePlayers();
    serialized::GameState serialize();
    private:
        std::shared_ptr<GameState> state;
        serialized::GameState serializedState;

};