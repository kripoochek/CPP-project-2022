#ifndef MY_TANKS_IN_LABIRINT_PLAYER_H
#define MY_TANKS_IN_LABIRINT_PLAYER_H

#include "Entity.h"

struct Player : Entity {
    Player(float x, float y, sf::Texture &texture);

    void update(float dt) final;
protected:

private:
    void initVariables();
    void initComponents();
};

#endif //MY_TANKS_IN_LABIRINT_PLAYER_H
