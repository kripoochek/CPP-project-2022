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
    if (movementComponent){
        movementComponent->update(dt);
    }
    if (hitboxComponent){
        hitboxComponent->update();
    }
}

void Entity::render(sf::RenderTarget& target) {
    target.draw(sprite);

    if (hitboxComponent){
        hitboxComponent->render(target);
    }
}

void Entity::initVariables() {
    movementComponent = nullptr;
}

void Entity::createMovementComponent(float maxVelocityMove, float maxVelocityRotate, float currentVelocityMove, float acceleration, float deceleration) {
    movementComponent = std::make_shared<MovementComponent>(sprite, maxVelocityMove, maxVelocityRotate, currentVelocityMove, acceleration, deceleration);
}

void Entity::createHitboxComponent(sf::Sprite &sprite, float offsetX, float offsetY, float width, float height) {
    hitboxComponent = std::make_shared<HitboxComponent>(sprite, offsetX, offsetY, width, height);
}

sf::FloatRect Entity::getGlobalBounds() const {
    if (hitboxComponent){ return hitboxComponent->getGlobalBounds(); }
    return sprite.getGlobalBounds();
}




