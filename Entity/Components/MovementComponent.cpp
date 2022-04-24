#include "MovementComponent.h"

#include <cmath>

MovementComponent::MovementComponent(sf::Sprite &sprite, float maxVelocityMove, float maxVelocityRotate,
                                     float currentVelocityMove,
                                     float acceleration, float deceleration) :
        sprite(sprite), maxVelocityMove(maxVelocityMove), maxVelocityRotate(maxVelocityRotate),
        acceleration(acceleration), deceleration(deceleration),
        currentVelocityMove(currentVelocityMove), intervalToStopMovement(std::chrono::duration<double>(0.01)) {
}

void MovementComponent::move(bool isForward, float dt) {
    lastMoveCommandTime = std::chrono::system_clock::now();

    float acc = (isForward ? acceleration : -acceleration);
    if (currentVelocityMove * acc < 0) { gracefullyReduceVelocity(dt); }
    currentVelocityMove += acc * dt;

    if (currentVelocityMove > 0) {
        currentVelocityMove = std::min(currentVelocityMove, maxVelocityMove);
    }
    else{
        currentVelocityMove = std::max(currentVelocityMove, -maxVelocityMove);
    }

    float angle = sprite.getRotation() * 3.1415f / 180;
    velocity.x = std::cos(angle) * currentVelocityMove;
    velocity.y = std::sin(angle) * currentVelocityMove;
}

void MovementComponent::rotate(bool clockwise, float dt) {
    float d_angle = (clockwise ? 1.0f : -1.0f);
    sprite.rotate(d_angle * maxVelocityRotate * dt);

    float angle = sprite.getRotation() * 3.1415f / 180;
    velocity.x = std::cos(angle) * currentVelocityMove;
    velocity.y = std::sin(angle) * currentVelocityMove;
}

void MovementComponent::update(float dt) {
    if (this->isStopMove()) { gracefullyReduceVelocity(dt); }
// regular movements
    sprite.move(velocity * dt);
}

sf::Vector2f MovementComponent::getVelocity() const { return velocity; }

bool MovementComponent::isStopMove() {
    auto currentTime = std::chrono::system_clock::now();
    std::chrono::duration<double> currentInterval = currentTime - lastMoveCommandTime;
    return (currentInterval > intervalToStopMovement);
}

void MovementComponent::gracefullyReduceVelocity(float dt) {
    if (currentVelocityMove > 0) {
        currentVelocityMove -= deceleration * dt;
        currentVelocityMove = std::max(currentVelocityMove, 0.f);
    } else if (currentVelocityMove < 0) {
        currentVelocityMove += deceleration * dt;
        currentVelocityMove = std::min(currentVelocityMove, 0.f);
    }

    float angle = sprite.getRotation() * 3.1415f / 180;
    velocity.x = std::cos(angle) * currentVelocityMove;
    velocity.y = std::sin(angle) * currentVelocityMove;
}

void MovementComponent::stopVelocity() { currentVelocityMove = 0; }

void MovementComponent::stopVelocityX() { velocity.x = 0; }

void MovementComponent::stopVelocityY() { velocity.y = 0; }