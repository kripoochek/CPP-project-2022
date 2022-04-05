#include "CollisionManager.h"
CollisionManager::CollisionManager(std::shared_ptr<Map> map_, std::vector<std::shared_ptr<Player>> players_): map(map_), players(players_) {
    activeWalls=map->getActiveWalls();

}

void CollisionManager::update() {
    //check hitboxes
    //1) walls and players
    for (auto wall : activeWalls){
        for (auto player : players){
            if (player->hitboxComponent->intersect(wall->hitboxComponent)){
                player->handleHitWall(wall);
            }
        }
    }
    //2) players and bullets
    //3) walls and bullets
    //4) players and players

    for (auto player1 : players){
        for (auto player2 : players){
            if (player1==player2) continue;
            if (player1->hitboxComponent->intersect(player2->hitboxComponent)){
                player1->handleHitTank(player2);
            }
        }
    }
}