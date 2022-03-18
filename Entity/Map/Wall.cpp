#include "Wall.h"
Wall::Wall(sf::Vector2f coordinates_, const sf::Texture &texture_, bool type_){
    if (type_){
        type=Type::horizontal;
    }
    else{
        type=Type::vertical;
    }
    setTexture(texture_);
    setPosition(coordinates_);

}

void Wall::setTexture(const sf::Texture &texture_) {
    sprite.setTexture(texture_);
}

void Wall::setPosition(sf::Vector2f coordinates) {
    sprite.setPosition(coordinates);
}

Type Wall::getType() {
    return type;
}

void Wall::render(std::shared_ptr<sf::RenderTarget> target) {
    target->draw(sprite);
}