#ifndef TANKS_IN_LABIRINT_CONTROLLER_H
#define TANKS_IN_LABIRINT_CONTROLLER_H
#include "DynamicObject.h"
#include "Tank.h"
#include "Bullet.h"
struct Controller {
public:
    Controller();
    std::vector<DynamicObject*> getTanks();
    std::vector<Bullet::Bullet*> getBullets();
    void tankMovement();
private:
    std::vector<DynamicObject*> tanks;
    std::vector<Bullet::Bullet*> bullets;
};

#endif //TANKS_IN_LABIRINT_CONTROLLER_H
