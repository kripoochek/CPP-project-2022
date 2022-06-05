#ifndef MY_TANKS_IN_LABIRINT_COLLISIONMANAGER_H
#define MY_TANKS_IN_LABIRINT_COLLISIONMANAGER_H

#include "Map.h"
#include "Player.h"
#include "Bullet.h"

struct CollisionManager {
    CollisionManager(std::shared_ptr<Map> map_, std::vector<std::shared_ptr<Player>> players_);
    void update(float dt);
private:
    std::shared_ptr<Map> map;
    std::vector<std::shared_ptr<Player>> players;
    std::vector<std::shared_ptr<Wall>> activeWalls;
    //add Bullets
};

#endif //MY_TANKS_IN_LABIRINT_COLLISIONMANAGER_H
