#ifndef MY_TANKS_IN_LABIRINT_PLAYER_H
#define MY_TANKS_IN_LABIRINT_PLAYER_H

#include "Entity.h"
#include "Wall.h"
#include "Bullet.h"

struct Player : Entity {
    Player(std::shared_ptr<b2World> world, float x, float y, int maxBulletCount, int id, sf::Texture &texture);

    void attack(std::set<std::pair<int, std::shared_ptr<Bullet>>> &bullets, sf::Texture &texture, float dt);
    void addBullet();
protected:

private:
    int id;

    std::chrono::time_point<std::chrono::system_clock, std::chrono::duration<double>> lastAttackCommandTime;
    std::chrono::duration<double> intervalNewAttack{};
    int bulletCount;


    void initSFML(float x, float y, sf::Texture& texture);
    void initBox2D(std::shared_ptr<b2World> initWorld);
    void initComponents();
};

#endif //MY_TANKS_IN_LABIRINT_PLAYER_H
