#ifndef GAME_BULLET_H
#define GAME_BULLET_H

#include "Entity.h"

struct Bullet : Entity {
    Bullet(float x, float y, float lifeTime, sf::Texture &texture);
protected:

private:
    void initVariables();
    void initComponents();

    float lifeTime = 4000;
};

#endif //GAME_BULLET_H