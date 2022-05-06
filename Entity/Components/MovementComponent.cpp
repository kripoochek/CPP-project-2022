#include "MovementComponent.h"

#include <cmath>

MovementComponent::MovementComponent(sf::Sprite &sprite, b2Body* body, float maxVelocityMove, float maxVelocityRotate,
                                     float currentVelocityMove,
                                     float acceleration, float deceleration) :
        sprite(sprite), body(body), maxVelocityMove(maxVelocityMove), maxVelocityRotate(maxVelocityRotate),
        acceleration(acceleration), deceleration(deceleration),
        currentVelocityMove(currentVelocityMove), intervalToStopMovement(std::chrono::duration<double>(0.01)) {
    angle=body->GetAngle();
}

void MovementComponent::move(bool isForward, float dt) {
    lastMoveCommandTime = std::chrono::system_clock::now();
    float acc=(isForward ? 1.0f:-1.0f);
    body->SetLinearVelocity(b2Vec2(acc*velocity.x,acc*velocity.y));
}

void MovementComponent::rotate(bool clockwise, float dt) {
    float d_angle = (clockwise ? 1.0f : -1.0f);
    angle+=d_angle*maxVelocityRotate*dt;
    body->SetTransform(body->GetPosition(),angle);
    velocity.x = std::cos(sprite.getRotation()*(3.1415f/180)) * currentVelocityMove;
    velocity.y = std::sin(sprite.getRotation()*(3.1415f/180)) * currentVelocityMove;
}

void MovementComponent::update(float dt) {
    if (this->isStopMove()) { gracefullyReduceVelocity(dt); }


}

sf::Vector2f MovementComponent::getVelocity() const { return velocity; }

bool MovementComponent::isStopMove() {
    auto currentTime = std::chrono::system_clock::now();
    std::chrono::duration<double> currentInterval = currentTime - lastMoveCommandTime;
    return (currentInterval > intervalToStopMovement);
}

void MovementComponent::gracefullyReduceVelocity(float dt) {
   /* if (currentVelocityMove > 0) {
        currentVelocityMove -= deceleration * dt;
        currentVelocityMove = std::max(currentVelocityMove, 0.f);
    } else if (currentVelocityMove < 0) {
        currentVelocityMove += deceleration * dt;
        currentVelocityMove = std::min(currentVelocityMove, 0.f);
    }

    float angle = sprite.getRotation() * 3.1415f / 180;
    velocity.x = std::cos(angle) * currentVelocityMove;
    velocity.y = std::sin(angle) * currentVelocityMove;*/
   body->SetLinearVelocity(b2Vec2(0,0));
}

void MovementComponent::stopVelocity() {  }

void MovementComponent::stopVelocityX() { velocity.x = 0; }

void MovementComponent::stopVelocityY() { velocity.y = 0; }