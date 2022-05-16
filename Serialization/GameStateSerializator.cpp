#include "proto/GameState.pb.h"
#include "../States/State.h"
#include "../States/GameState.h"
#include "GameStateSerializator.h"
#include "../Entity/Map/Map.h"
#include "GameTextures.h"

#include <iostream>

GameStateSerializator::GameStateSerializator(std::shared_ptr<GameState> gameState) : state(gameState){}


void GameStateSerializator::serializePlayers() {
    for (int i = 0; i < state->players.size(); i++) {
        serialized::Player player;
        if (state->players[i] != nullptr) {
            auto pos = state->players[i]->getPosition();
            player.set_x(pos.x);
            player.set_y(pos.y);
            player.set_id(state->players[i]->getId());
            serializedState.add_players()->CopyFrom(player);
        } else {
            player.set_x(0);
            player.set_y(0);
            player.set_id(-1);
            serializedState.add_players()->CopyFrom(player);
        }
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

void GameStateSerializator::deserializeMap(serialized::GameState &serializedState, std::shared_ptr<Map> gameMap, sf::Texture& verticalTexture, sf::Texture& horizontalTexture) {
    for (int i = 0; i < serializedState.map().rowsnumber(); i++) {
        auto mapRow = serializedState.map().rows().at(i);
        for (int j = 0; j < serializedState.map().columnsnumber(); j++) {
            auto mapBox = mapRow.boxes().at(j);
            Edges edges = gameMap->map[i][j]->getEdges();
            if (edges.upper == nullptr){
                std::shared_ptr<Wall> upper = std::make_shared<Wall>(mapBox.upperwall().x(), mapBox.upperwall().y(), horizontalTexture);
                upper->setHidden(mapBox.upperwall().ishidden());
                gameMap->map[i][j]->addEdge(upper, "upper");
                if (i - 1 >= 0){
                    gameMap->map[i - 1][j]->addEdge(upper,"lower");
                }
            }
            if (edges.lower == nullptr){
                std::shared_ptr<Wall> lower = std::make_shared<Wall>(mapBox.lowerwall().x(), mapBox.lowerwall().y(), horizontalTexture);
                lower->setHidden(mapBox.lowerwall().ishidden());
                gameMap->map[i][j]->addEdge(lower, "lower");
                if (i + 1 < serializedState.map().rowsnumber()){
                    gameMap->map[i + 1][j]->addEdge(lower, "upper");
                }
            }
            if (edges.left == nullptr){
                std::shared_ptr<Wall> left = std::make_shared<Wall>(mapBox.leftwall().x(), mapBox.leftwall().y(), verticalTexture);
                left->setHidden(mapBox.leftwall().ishidden());
                gameMap->map[i][j]->addEdge(left, "left");
                if (j - 1 >= 0){
                    gameMap->map[i][j - 1]->addEdge(left, "right");
                }
            }
            if (edges.right == nullptr){
                std::shared_ptr<Wall> right = std::make_shared<Wall>(mapBox.rightwall().x(), mapBox.rightwall().y(), verticalTexture);
                right->setHidden(mapBox.rightwall().ishidden());
                gameMap->map[i][j]->addEdge(right, "right");
                if (j + 1 < serializedState.map().columnsnumber()){
                    gameMap->map[i][j + 1]->addEdge(right, "left");
                }
            }
        }
    }
};

void GameStateSerializator::deserializePlayers(serialized::GameState &serializedState, std::vector<std::shared_ptr<Player>> &gamePlayers, std::shared_ptr<GameTextures> gameTextures) {
    for (int i = 0; i < serializedState.players_size(); i++) {
        auto player = serializedState.players().at(i);
        if (player.id() == -1) {
            gamePlayers.push_back(nullptr);
            continue;
        }
        gamePlayers.push_back( std::make_shared<Player>(player.x(), player.y(), 0, player.id(), gameTextures->getPlayerTextureById(player.id())) );
    }
};