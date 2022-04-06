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
    if (currentVelocityMove * acc < 0) {
        gracefullyReduceVelocity(dt);
    }
    currentVelocityMove += acc * dt;

    if (currentVelocityMove > 0 && currentVelocityMove > maxVelocityMove) {
        currentVelocityMove = maxVelocityMove;
    } else if (currentVelocityMove < 0 && currentVelocityMove < -maxVelocityMove) {
        currentVelocityMove = -maxVelocityMove;
    }
}

void MovementComponent::rotate(bool clockwise, float dt) {
    float d_angle = (clockwise ? 1.0f : -1.0f);
    sprite.rotate(d_angle * maxVelocityRotate * dt);
}

void MovementComponent::update(float dt) {
    if (this->isStopMove()) {
        gracefullyReduceVelocity(dt);
    }

    // regular movements
    float angle = sprite.getRotation() * 3.1415f / 180;
    velocity.x = std::cos(angle) * currentVelocityMove;
    velocity.y = std::sin(angle) * currentVelocityMove;
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
}

void MovementComponent::stop() {
    currentVelocityMove = -55;

}

void MovementComponent::snapBack(std::shared_ptr<Wall> wall) {
    sf::FloatRect playerBounds = sprite.getGlobalBounds();
    sf::FloatRect wallBounds = wall->hitboxComponent->getGlobalBounds();
    //bottom
    if (playerBounds.top < wallBounds.top
        && playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
        && playerBounds.left < wallBounds.left + wallBounds.width
        && playerBounds.left + playerBounds.width > wallBounds.left) {
        velocity.y = 0.f;
        sprite.setPosition(playerBounds.left+playerBounds.width/2, wallBounds.top - playerBounds.height/2);
    }
        //top
    else if (playerBounds.top > wallBounds.top
             && playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
             && playerBounds.left < wallBounds.left + wallBounds.width
             && playerBounds.left + playerBounds.width > wallBounds.left) {
        velocity.y = 0.f;
        sprite.setPosition(playerBounds.left+playerBounds.width/2, wallBounds.top + wallBounds.height/2);
    }
    //right
    if (playerBounds.left < wallBounds.left
    && playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
    && playerBounds.top < wallBounds.top + wallBounds.height
    && playerBounds.top + playerBounds.height > wallBounds.top)
    {
        velocity.x=0.f;
        sprite.setPosition(wallBounds.left-playerBounds.width/2,playerBounds.top+playerBounds.height/2);
    }

    //left
    else if (playerBounds.left > wallBounds.left
             && playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
             && playerBounds.top > wallBounds.top + wallBounds.top + wallBounds.height
             && playerBounds.top + playerBounds.height > wallBounds.top)
    {
        velocity.x=0.f;
        sprite.setPosition(wallBounds.left + wallBounds.width +playerBounds.width/2,playerBounds.top+playerBounds.height/2);
    }

}
