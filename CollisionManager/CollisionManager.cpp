#include "CollisionManager.h"

CollisionManager::CollisionManager(std::shared_ptr<Map> map_, std::vector<std::shared_ptr<Player>> players_) : map(
        map_), players(players_) {
    activeWalls = map->getActiveWalls();
}

void CollisionManager::update(float dt) {
    //check hitboxes
    //1) walls and players
    for (auto& wall: activeWalls) {
        for (auto& player: players) {
            sf::FloatRect playerBounds = player->getGlobalBounds();
            sf::FloatRect wallBounds = wall->getGlobalBounds();
            sf::FloatRect nextPositionBounds = player->getNextPositionBounds(dt);

            if (!nextPositionBounds.intersects(wall->getGlobalBounds())) { continue; }

            //Bottom collision
            if (playerBounds.top < wallBounds.top
                && playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
                && playerBounds.left < wallBounds.left + wallBounds.width
                && playerBounds.left + playerBounds.width > wallBounds.left){
                player->stopVelocity();
                player->setPosition(playerBounds.left + playerBounds.width / 2, wallBounds.top - playerBounds.height / 2);
            }

                //Top collision
            else if (playerBounds.top > wallBounds.top
                     && playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
                     && playerBounds.left < wallBounds.left + wallBounds.width
                     && playerBounds.left + playerBounds.width > wallBounds.left){
                player->stopVelocity();
                player->setPosition(playerBounds.left + playerBounds.width / 2, wallBounds.top + wallBounds.height + playerBounds.height / 2);
            }

            //Right collision
            if (playerBounds.left < wallBounds.left
                && playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
                && playerBounds.top < wallBounds.top + wallBounds.height
                && playerBounds.top + playerBounds.height > wallBounds.top){
                player->stopVelocity();
                player->setPosition(wallBounds.left - playerBounds.width + playerBounds.width / 2,
                                    playerBounds.top + playerBounds.height / 2);
            }

                //Left collision
            else if (playerBounds.left > wallBounds.left
                     && playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
                     && playerBounds.top < wallBounds.top + wallBounds.height
                     && playerBounds.top + playerBounds.height > wallBounds.top){
                player->stopVelocity();
                player->setPosition(wallBounds.left + wallBounds.width + playerBounds.width / 2, playerBounds.top + playerBounds.height / 2);
            }
        }
    }


    //2) players and bullets
    //3) walls and bullets
    //4) players and players

    for (auto& player1: players) {
        for (auto& player2: players) {
            if (player1 == player2) continue;
            sf::FloatRect playerBounds = player1->getGlobalBounds();
            sf::FloatRect wallBounds = player2->getGlobalBounds();
            sf::FloatRect nextPositionBounds = player1->getNextPositionBounds(dt);

            if (!nextPositionBounds.intersects(player2->getGlobalBounds())) continue;
        }
    }
}