#include "MovementComponent.h"


MovementComponent::MovementComponent(sf::Sprite& sprite, float maxVelocityMove, float maxVelocityRotate) :
sprite(sprite), maxVelocityMove(maxVelocityMove), maxVelocityRotate(maxVelocityRotate) {

}

void MovementComponent::move(bool forward, float dt) {
    float angle = sprite.getRotation() * 3.1415/180;
    velocity.x = cos(angle) * maxVelocityMove;
    velocity.y = sin(angle) * maxVelocityMove;
    sprite.move(velocity * (forward ? 1.f : -1.f) * dt);
}

void MovementComponent::rotate(bool clockwise, float dt) {
    float d_angle = (clockwise ? 1.0f : -1.0f);
    sprite.rotate(d_angle * maxVelocityRotate * dt);
}
void MovementComponent::update(float dt) {

}

sf::Vector2f MovementComponent::getVelocity() const { return velocity; }



