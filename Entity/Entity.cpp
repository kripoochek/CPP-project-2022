#include "Entity.h"

Entity::Entity() {
    initVariables();
}

void Entity::setTexture(sf::Texture &texture) {
    sprite.setTexture(texture);
}

void Entity::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

void Entity::move(float dt, float dir_x, float dir_y) {
    if (!movementComponent){ return; }
    movementComponent->move(dir_x, dir_y, dt);
}

void Entity::update(float dt) {

}

void Entity::render(std::shared_ptr<sf::RenderTarget> target) {
    target->draw(sprite);
}

void Entity::initVariables() {
    movementComponent = nullptr;
}

void Entity::createMovementComponent(float maxVelocity) {
    movementComponent = std::make_shared<MovementComponent>(sprite, maxVelocity);
}




