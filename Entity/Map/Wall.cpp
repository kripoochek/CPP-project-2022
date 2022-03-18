#include "Wall.h"
Wall::Wall(sf::Vector2f coordinates_):coordinates(coordinates_) {
}

void Wall::initSize(bool position) {
    if (position){
        wall.setScale(80,20);
    }
    else{
        wall.setScale(20,80);
    }
    
}