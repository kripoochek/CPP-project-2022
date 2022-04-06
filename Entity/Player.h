#ifndef MY_TANKS_IN_LABIRINT_PLAYER_H
#define MY_TANKS_IN_LABIRINT_PLAYER_H

#include "Entity.h"
#include "Wall.h"
#include "Bullet.h"

struct Player : Entity {
    Player(float x, float y, int maxBulletCount, int id, sf::Texture &texture);

    void handleHitTank(std::shared_ptr<Player> other);
    void handleHitWall(std::shared_ptr<Wall> other);

    void attack(std::deque<std::pair<int, std::shared_ptr<Bullet>>> &bullets, sf::Texture &texture, float dt);
    void addBullet();
protected:

private:
    void initVariables();
    void initComponents();

    int id;

    std::chrono::time_point<std::chrono::system_clock, std::chrono::duration<double>> lastAttackCommandTime;
    std::chrono::duration<double> intervalNewAttack{};
    int bulletCount;

};

#endif //MY_TANKS_IN_LABIRINT_PLAYER_H
