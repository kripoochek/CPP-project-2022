#ifndef GAME_BULLET_H
#define GAME_BULLET_H

#include "Entity.h"
#include <chrono>

struct Bullet : Entity {
    Bullet(std::shared_ptr<b2World> world, float x, float y, float angle, float lifeTime, sf::Texture &texture);

    bool isDeathTime();
protected:

private:
    std::chrono::time_point<std::chrono::system_clock, std::chrono::duration<double>> initTime;
    std::chrono::duration<double> lifeTime;

    void initSFML(float x, float y, float angle, sf::Texture& texture);
    void initBox2D(std::shared_ptr<b2World> initWorld);
    void initComponents();
};

#endif //GAME_BULLET_H