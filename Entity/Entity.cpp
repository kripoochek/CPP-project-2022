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

void Entity::move(bool forward, float dt) {
    if (!movementComponent){ return; }
    movementComponent->move(forward, dt);
}

void Entity::rotate(bool clockwise, float dt) {
    if (!movementComponent) { return; }
    movementComponent->rotate(clockwise, dt);
}

void Entity::update(float dt) {
    this->movementComponent->update(dt);
}

void Entity::render(const std::shared_ptr<sf::RenderTarget>& target) {
    target->draw(sprite);
}

void Entity::initVariables() {
    movementComponent = nullptr;
}

void Entity::createMovementComponent(float maxVelocityMove, float maxVelocityRotate) {
    movementComponent = std::make_shared<MovementComponent>(sprite, maxVelocityMove, maxVelocityRotate);
}




