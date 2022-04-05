#ifndef GAME_BULLET_H
#define GAME_BULLET_H

#include "Entity.h"
#include <chrono>

struct Bullet : Entity {
    Bullet(float x, float y, float angle, float lifeTime, sf::Texture &texture);

    bool isDeathTime();
protected:

private:
    void initVariables();
    void initComponents();

    std::chrono::time_point<std::chrono::system_clock, std::chrono::duration<double>> initTime;
    std::chrono::duration<double> lifeTime;
};

#endif //GAME_BULLET_H