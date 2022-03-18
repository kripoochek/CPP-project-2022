#include "Wall.h"
Wall::Wall(sf::Vector2f coordinates_, const sf::Texture &texture_, bool position) {
    initSize(position);
    setTexture(texture_);
    setPosition(coordinates_);
}

void Wall::initSize(bool position) {
    if (position){
        wall.setScale(80,20);
    }
    else{
        wall.setScale(20,80);
    }
}

void Wall::setTexture(const sf::Texture &texture_) {
    wall.setTexture(texture_);
}

void Wall::setPosition(sf::Vector2f coordinates) {
    wall.setPosition(coordinates);
}
