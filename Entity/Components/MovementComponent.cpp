#include "MovementComponent.h"

#include <utility>


MovementComponent::MovementComponent(sf::Sprite& sprite, float maxVelocity) : sprite(sprite), maxVelocity(maxVelocity) {

}

void MovementComponent::move(float dir_x, float dir_y, float dt) {
    velocity.x = maxVelocity * dir_x;
    velocity.y = maxVelocity * dir_y;

    sprite.move(velocity * dt);
}

void MovementComponent::update(float dt) {

}

sf::Vector2f MovementComponent::getVelocity() const { return velocity; }



