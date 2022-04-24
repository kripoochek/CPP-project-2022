#include "proto/GameState.pb.h"
#include "../States/State.h"
#include "../States/GameState.h"
#include "GameStateSerializator.h"
#include <iostream>

GameStateSerializator::GameStateSerializator(std::shared_ptr<GameState> gameState) : state(gameState){};
void GameStateSerializator::serializePlayers() {
    for (int i = 0; i < state->players.size(); i++) {
        serialized::Player player;
        auto pos = state->players[i]->getPosition();
        player.set_x(pos.x);
        player.set_y(pos.y);
        player.set_id(i + 1);
        serializedState.add_players()->CopyFrom(player);
    }
}

void GameStateSerializator::serializeMap() {
    serialized::Map* serializedMap = serializedState.mutable_map();
    serializedMap->set_x(100);
    serializedMap->set_y(100);
    serializedMap->set_rowsnumber(state->map->rows);
    serializedMap->set_columnsnumber(state->map->columns);
    auto boxes = state->map->getBoxes();
    for (int i = 0; i < state->map->rows; i++) {
        serialized::MapBoxesRow* serializedRow = serializedMap->add_rows();
        for (int j = 0; j < state->map->columns; j++) {
            serialized::MapBox* serializedMapBox = serializedRow->add_boxes();
            serializedMapBox->set_x(boxes[i][j]->getCoordinates().x);
            serializedMapBox->set_y(boxes[i][j]->getCoordinates().y);

            serialized::MapBoxWall* leftWall = serializedMapBox->mutable_leftwall();
            leftWall->set_x(boxes[i][j]->getEdges().left->getPosition().x);
            leftWall->set_y(boxes[i][j]->getEdges().left->getPosition().y);
            leftWall->set_ishidden(boxes[i][j]->getEdges().left->isHidden());

            serialized::MapBoxWall* topWall = serializedMapBox->mutable_upperwall();
            topWall->set_x(boxes[i][j]->getEdges().upper->getPosition().x);
            topWall->set_y(boxes[i][j]->getEdges().upper->getPosition().y);
            topWall->set_ishidden(boxes[i][j]->getEdges().upper->isHidden());

            serialized::MapBoxWall* rightWall = serializedMapBox->mutable_rightwall();
            rightWall->set_x(boxes[i][j]->getEdges().right->getPosition().x);
            rightWall->set_y(boxes[i][j]->getEdges().right->getPosition().y);
            rightWall->set_ishidden(boxes[i][j]->getEdges().right->isHidden());

            serialized::MapBoxWall* downWall = serializedMapBox->mutable_lowerwall();
            downWall->set_x(boxes[i][j]->getEdges().lower->getPosition().x);
            downWall->set_y(boxes[i][j]->getEdges().lower->getPosition().y);
            downWall->set_ishidden(boxes[i][j]->getEdges().lower->isHidden());
        }
    }
}

serialized::GameState GameStateSerializator::serialize() {
    serializePlayers();
    serializeMap();
    return serializedState;
}