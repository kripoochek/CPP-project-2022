#ifndef TANKS_IN_LABIRINT_TANK_H
#define TANKS_IN_LABIRINT_TANK_H

#include "DynamicObject.h"

struct Tank : DynamicObject {
    Tank(float x, float y, const std::string &file);

    void setTexture(const std::string &file) override;
    bool intersects(Tank &other);
};


#endif //TANKS_IN_LABIRINT_TANK_H
