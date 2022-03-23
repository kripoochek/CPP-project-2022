#include "Wall.h"

Wall::Wall(sf::Vector2f coordinates_, const sf::Texture &texture_) {
    setTexture(texture_);
    setPosition(coordinates_);
    sprite.setScale((sprite.getTexture()->getSize().x<=100 ? 1.0 : 100.0/sprite.getTexture()->getSize().x) ,(sprite.getTexture()->getSize().y<=100 ? 1.0 : 100.0/sprite.getTexture()->getSize().y));
    sprite.setOrigin(sprite.getTexture()->getSize().x/2,sprite.getTexture()->getSize().y/2);
    initComponents();
}

void Wall::setTexture(const sf::Texture &texture_) {
    sprite.setTexture(texture_);
}

void Wall::setPosition(sf::Vector2f coordinates) {
    sprite.setPosition(coordinates);
}


void Wall::render(sf::RenderTarget& target) {
    if (!hidden) {
        target.draw(sprite);
    }
    if (hitboxComponent){
        hitboxComponent->render(target);
    }
}
void Wall::createHitboxComponent(sf::Sprite &sprite, float offsetX, float offsetY, float width, float height) {
    hitboxComponent = std::make_shared<HitboxComponent>(sprite, offsetX, offsetY, width, height);
}
void Wall::initComponents() {

    createHitboxComponent(sprite, 0, 0, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
}