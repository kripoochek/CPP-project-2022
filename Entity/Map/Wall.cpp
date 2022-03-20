#include "Wall.h"

Wall::Wall(sf::Vector2f coordinates_, const sf::Texture &texture_) {
    setTexture(texture_);
    setPosition(coordinates_);
    sprite.setScale(0.5, 0.5);
}

void Wall::setTexture(const sf::Texture &texture_) {
    sprite.setTexture(texture_);
}

void Wall::setPosition(sf::Vector2f coordinates) {
    sprite.setPosition(coordinates);
}


void Wall::render(std::shared_ptr<sf::RenderTarget> target) {
    if (!hidden) {
        target->draw(sprite);
    }
}