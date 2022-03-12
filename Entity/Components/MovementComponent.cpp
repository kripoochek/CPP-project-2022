#include "MovementComponent.h"

#include <utility>


MovementComponent::MovementComponent(sf::Sprite& sprite, float maxVelocity) : sprite(sprite), maxVelocity(maxVelocity) {

}

void MovementComponent::move(float dir_x, float dir_y, float dt) {
    double angle=sprite.getRotation()*3.1415/180;
    velocity.x = cos(angle)*maxVelocity * dir_x;
    velocity.y = sin(angle)*maxVelocity * dir_y;
    sprite.move(velocity * dt);
}

void MovementComponent::rotate(bool turnDir_) {
    float turnDir=(turnDir_ ? 1.0f : -1.0f);
    float currentAngle=sprite.getRotation();
    sprite.setRotation(currentAngle+turnDir);
}
void MovementComponent::update(float dt) {

}

sf::Vector2f MovementComponent::getVelocity() const { return velocity; }



