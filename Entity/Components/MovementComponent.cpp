#include "MovementComponent.h"




MovementComponent::MovementComponent(sf::Sprite &sprite, b2Body *body, float velocityMove,
                                     float velocityRotate) : sprite(sprite), body(body), velocityMove(velocityMove),
                                                             velocityRotate(velocityRotate), intervalToStopMovement(
                std::chrono::duration<double>(0.01)) {
    angle = body->GetAngle();

}


void MovementComponent::move(bool isForward, float dt) {
    lastMoveCommandTime = std::chrono::system_clock::now();
    float acc = (isForward ? 1.0f : -1.0f);
    body->SetLinearVelocity(b2Vec2(acc * velocity.x, acc * velocity.y));
}

void MovementComponent::rotate(bool clockwise, float dt) {
    float d_angle = (clockwise ? 1.0f : -1.0f);
    angle += d_angle * velocityRotate * dt;
    body->SetTransform(body->GetPosition(), angle);
    velocity.x = std::cos(sprite.getRotation() * (3.1415f / 180)) * velocityMove;
    velocity.y = std::sin(sprite.getRotation() * (3.1415f / 180)) * velocityMove;
}

void MovementComponent::update(float dt) {
    if (this->isStopMove() && velocityRotate) { gracefullyReduceVelocity(dt); }
}

sf::Vector2f MovementComponent::getVelocity() const { return velocity; }

bool MovementComponent::isStopMove() {
    auto currentTime = std::chrono::system_clock::now();
    std::chrono::duration<double> currentInterval = currentTime - lastMoveCommandTime;
    return (currentInterval > intervalToStopMovement);
}

void MovementComponent::gracefullyReduceVelocity(float dt) {
    body->SetLinearVelocity(b2Vec2(0, 0));
}

void MovementComponent::stopVelocity() {}

void MovementComponent::stopVelocityX() { velocity.x = 0; }

void MovementComponent::stopVelocityY() { velocity.y = 0; }


