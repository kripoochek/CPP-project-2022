#include "Entity.h"

void Entity::setTexture(sf::Texture &texture) { sprite.setTexture(texture); }

void Entity::setPosition(float x, float y) { sprite.setPosition(x, y); }

void Entity::move(bool forward, float dt) {
    if (!alive){
        return;
    }

    if (!movementComponent){ return; }
    movementComponent->move(forward, dt);
}

void Entity::rotate(bool clockwise, float dt) {
    if (!alive){
        return;
    }

    if (!movementComponent) { return; }
    movementComponent->rotate(clockwise, dt);
}

void Entity::update(float dt) {
    if (!alive){
        return;
    }

    if (movementComponent){ movementComponent->update(dt); }
    if (hitboxComponent){ hitboxComponent->update(); }
    body->SetAngularVelocity(0);
    b2Vec2 pos = body->GetPosition();
    float ang = body->GetAngle();
    sprite.setPosition(pos.x*SCALE,pos.y*SCALE);
    sprite.setRotation(ang*SCALE);
}

void Entity::render(sf::RenderTarget& target) {
    if (!alive){
        return;
    }

    target.draw(sprite);
    if (hitboxComponent){
        hitboxComponent->render(target);
    }
}

void Entity::initVariables() {
    movementComponent = nullptr;
    hitboxComponent = nullptr;
}

void Entity::createMovementComponent(float velocityMove, float velocityRotate) {
    movementComponent = std::make_shared<MovementComponent>(sprite, body, velocityMove, velocityRotate);
}

void Entity::createHitboxComponent(sf::Sprite &sprite, float offsetX, float offsetY, float width, float height) {
    hitboxComponent = std::make_shared<HitboxComponent>(sprite, offsetX, offsetY, width, height);
}

sf::FloatRect Entity::getGlobalBounds() const {
    if (hitboxComponent){ return hitboxComponent->getGlobalBounds(); }
    return sprite.getGlobalBounds();
}

const sf::Vector2f &Entity::getPosition() const {
    if (hitboxComponent){ return hitboxComponent->getPosition();}
    return sprite.getPosition();
}

const sf::Vector2f &Entity::getSpritePosition() const { return sprite.getPosition(); }

sf::FloatRect Entity::getNextPositionBounds(float dt) const {
    if (hitboxComponent && movementComponent){
        return hitboxComponent->getNextPosition(dt * movementComponent->getVelocity());
    }
    return sf::FloatRect(-1, -1, -1, -1);
}

void Entity::setPosition(sf::Vector2f &coordinates) { sprite.setPosition(coordinates); }

void Entity::stopVelocity() { movementComponent->stopVelocity(); }

void Entity::stopVelocityX() { movementComponent->stopVelocityX(); }

void Entity::stopVelocityY() { movementComponent->stopVelocityY(); }

void Entity::setOrigin(float x, float y) {
    if (hitboxComponent){ hitboxComponent->setOrigin(x, y);}
    sprite.setOrigin(x, y);
}

bool Entity::isAlive() {
    return alive;
}

void Entity::killObject() {
    alive = false;
    world->DestroyBody(body);
}

float Entity::getRotation() {
    return sprite.getRotation();
}

void Entity::setRotation(float newRotation) {
    sprite.setRotation(newRotation);
}