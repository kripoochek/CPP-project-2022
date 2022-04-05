#ifndef MY_TANKS_IN_LABIRINT_PLAYER_H
#define MY_TANKS_IN_LABIRINT_PLAYER_H

#include "Entity.h"
#include "Wall.h"
struct Player : Entity {
    Player(float x, float y, sf::Texture &texture);
    void handleHitTank(std::shared_ptr<Player> other);
    void handleHitWall(std::shared_ptr<Wall> other);
    void update(float dt) final;
protected:

private:
    void initVariables();
    void initComponents();
};

#endif //MY_TANKS_IN_LABIRINT_PLAYER_H
