#include "proto/GameState.pb.h"
#include "../States/State.h"
#include "../States/RoundState.h"
#include "GameStateSerializator.h"
#include "../Entity/Map/Map.h"
#include "GameTextures.h"

#include <iostream>

void GameStateSerializator::serializePlayers(serialized::GameState& serializedState, std::shared_ptr<RoundState> state) {
    for (int i = 0; i < state->getPlayers().size(); i++) {
        serialized::Player player;
        if (state->getPlayers()[i] != nullptr && state->getPlayers()[i].get()->isAlive()) {
            auto pos = state->getPlayers()[i]->getPosition();
            player.set_x(pos.x);
            player.set_y(pos.y);
            player.set_id(state->getPlayers()[i]->getId());
            player.set_rotationangle(state->getPlayers()[i]->getRotation());
            serializedState.add_players()->CopyFrom(player);
        } else {
            player.set_x(0);
            player.set_y(0);
            player.set_id(-1);
            player.set_rotationangle(0);
            serializedState.add_players()->CopyFrom(player);
        }
    }
}

void GameStateSerializator::deserializePlayers(std::shared_ptr<b2World> world, serialized::GameState &serializedState, std::vector<std::shared_ptr<Player>> &gamePlayers, std::shared_ptr<GameTextures> gameTextures) {
    for (int i = 0; i < serializedState.players_size(); i++) {
        auto player = serializedState.players()[i];
        if (player.id() == -1) {
            gamePlayers.push_back(nullptr);
            continue;
        }
        auto gamePlayer = std::make_shared<Player>(world, player.x(), player.y(), 0, player.id(), gameTextures->getPlayerTextureById(player.id()));
        gamePlayer->setRotation(player.rotationangle());
        gamePlayers.push_back( gamePlayer );
    }
};

serialized::Map GameStateSerializator::serializeMap(std::shared_ptr<RoundState> state) {
    serialized::Map serializedMap;
    serializedMap.set_x(100);
    serializedMap.set_y(100);
    serializedMap.set_rowsnumber(state->getMap()->rows);
    serializedMap.set_columnsnumber(state->getMap()->columns);
    auto boxes = state->getMap()->getBoxes();
    for (int i = 0; i < state->getMap()->rows; i++) {
        serialized::MapBoxesRow* serializedRow = serializedMap.add_rows();
        for (int j = 0; j < state->getMap()->columns; j++) {
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
    return serializedMap;
}

serialized::GameState GameStateSerializator::serialize(std::shared_ptr<RoundState> gameState) {
    serialized::GameState serializedGameState;
    serializePlayers(serializedGameState, gameState);
    serializeBullets(serializedGameState, gameState);
    return serializedGameState;
}

void GameStateSerializator::deserializeMap(std::shared_ptr<b2World> world, serialized::Map &serializedMap, std::shared_ptr<Map> gameMap, sf::Texture& verticalTexture, sf::Texture& horizontalTexture) {
    for (int i = 0; i < serializedMap.rowsnumber(); i++) {
        auto mapRow = serializedMap.rows()[i];
        for (int j = 0; j < serializedMap.columnsnumber(); j++) {
            auto mapBox = mapRow.boxes()[j];
            Edges edges = gameMap->getBoxes()[i][j]->getEdges();
            if (edges.upper == nullptr){
                std::shared_ptr<Wall> upper = std::make_shared<Wall>(world, mapBox.upperwall().x(), mapBox.upperwall().y(), horizontalTexture);
                upper->setHidden(mapBox.upperwall().ishidden());
                gameMap->getBoxes()[i][j]->addEdge(upper, "upper");
                if (i - 1 >= 0){
                    gameMap->getBoxes()[i - 1][j]->addEdge(upper,"lower");
                }
            }
            if (edges.lower == nullptr){
                std::shared_ptr<Wall> lower = std::make_shared<Wall>(world, mapBox.lowerwall().x(), mapBox.lowerwall().y(), horizontalTexture);
                lower->setHidden(mapBox.lowerwall().ishidden());
                gameMap->getBoxes()[i][j]->addEdge(lower, "lower");
                if (i + 1 < serializedMap.rowsnumber()){
                    gameMap->getBoxes()[i + 1][j]->addEdge(lower, "upper");
                }
            }
            if (edges.left == nullptr){
                std::shared_ptr<Wall> left = std::make_shared<Wall>(world, mapBox.leftwall().x(), mapBox.leftwall().y(), verticalTexture);
                left->setHidden(mapBox.leftwall().ishidden());
                gameMap->getBoxes()[i][j]->addEdge(left, "left");
                if (j - 1 >= 0){
                    gameMap->getBoxes()[i][j - 1]->addEdge(left, "right");
                }
            }
            if (edges.right == nullptr){
                std::shared_ptr<Wall> right = std::make_shared<Wall>(world, mapBox.rightwall().x(), mapBox.rightwall().y(), verticalTexture);
                right->setHidden(mapBox.rightwall().ishidden());
                gameMap->getBoxes()[i][j]->addEdge(right, "right");
                if (j + 1 < serializedMap.columnsnumber()){
                    gameMap->getBoxes()[i][j + 1]->addEdge(right, "left");
                }
            }
        }
    }
};

void GameStateSerializator::serializeBullets(serialized::GameState& serializedState, std::shared_ptr<RoundState> state) {
    auto bulletsCopy = state->getBullets();
    for (auto it = bulletsCopy.begin(); it != bulletsCopy.end(); it++) {
        if (it == bulletsCopy.end()) break;
        serialized::Bullet serializedBullet;
        serializedBullet.set_x((*it).second->getPosition().x);
        serializedBullet.set_y((*it).second->getPosition().y);
        serializedBullet.set_rotationangle((*it).second->getRotation());
        serializedState.add_bullets()->CopyFrom(serializedBullet);
    }
}

void GameStateSerializator::deserializeBullets(std::shared_ptr<b2World> world, serialized::GameState &serializedState, std::set<std::pair<int, std::shared_ptr<Bullet>>> &gameBullets, sf::Texture& bulletTexture, int bulletsNumber) {
    for (int i = 0; i < bulletsNumber; i++) {
        auto bullet = serializedState.bullets()[i];
        gameBullets.insert({ 0, std::make_shared<Bullet>(
            world, bullet.x(), bullet.y(), bullet.rotationangle(), 1, bulletTexture
        )});
    }
}
