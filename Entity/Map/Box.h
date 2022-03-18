
#ifndef MY_TANKS_IN_LABIRINT_BOX_H
#define MY_TANKS_IN_LABIRINT_BOX_H

#include "Wall.h"
#include <vector>
#include <memory>
class Box {
private:
    std::vector<std::shared_ptr<Wall>> edges;
    sf::Sprite box;
private:
    Box();

};


#endif //MY_TANKS_IN_LABIRINT_BOX_H
