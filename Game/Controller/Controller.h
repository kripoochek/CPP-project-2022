#ifndef TANKS_IN_LABIRINT_CONTROLLER_H
#define TANKS_IN_LABIRINT_CONTROLLER_H
#include "DynamicObject.h"
#include "Tank.h"
struct Controller {
public:
    Controller();
    std::vector<DynamicObject*> getObjects();
    void tankMovement();
private:
    std::vector<DynamicObject*> objects;
};

#endif //TANKS_IN_LABIRINT_CONTROLLER_H
