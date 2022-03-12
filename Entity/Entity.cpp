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

void Entity::rotate(bool turnDir_) {
    if (!movementComponent) {return;}
    movementComponent->rotate(turnDir_);
}
void Entity::update(float dt) {

}

void Entity::render(std::shared_ptr<sf::RenderTarget> target) {
    target->draw(sprite);
}

void Entity::initVariables() {
    movementComponent = nullptr;
    this->sprite.setOrigin(200,200);
}

void Entity::createMovementComponent(float maxVelocity) {
    movementComponent = std::make_shared<MovementComponent>(sprite, maxVelocity);
}




