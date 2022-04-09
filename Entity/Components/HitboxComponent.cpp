#include "HitboxComponent.h"
#include <cassert>

HitboxComponent::HitboxComponent(sf::Sprite& sprite, float offsetX, float offsetY, float width, float height) :
    sprite(sprite), offsetX(offsetX), offsetY(offsetY) {
    hitbox.setPosition(sprite.getPosition().x + offsetX, sprite.getPosition().y + offsetY);
    hitbox.setSize(sf::Vector2f(width, height));
    hitbox.setOrigin(width / 2, height / 2);
    hitbox.setFillColor(sf::Color::Transparent);
    hitbox.setOutlineThickness(1.f);
    hitbox.setOutlineColor(sf::Color::Green);
}

bool HitboxComponent::intersects(const sf::FloatRect &frect) {
    return sprite.getGlobalBounds().intersects(frect);
}

void HitboxComponent::update() {
    hitbox.setPosition(sprite.getPosition().x + offsetX, sprite.getPosition().y + offsetY);
    hitbox.setRotation(sprite.getRotation());
}

void HitboxComponent::render(sf::RenderTarget &target) {
    target.draw(hitbox);
}

sf::FloatRect HitboxComponent::getGlobalBounds() const {
    return hitbox.getGlobalBounds();
}

const sf::Vector2f &HitboxComponent::getPosition() const {
    return hitbox.getPosition();
}

sf::FloatRect HitboxComponent::getNextPosition(const sf::Vector2f &velocity) {
    hitbox.setPosition(hitbox.getPosition().x + velocity.x, hitbox.getPosition().y + velocity.y);
    sf::FloatRect nextPosition = hitbox.getGlobalBounds();
    hitbox.setPosition(hitbox.getPosition().x - velocity.x, hitbox.getPosition().y - velocity.y);
    return nextPosition;
}

bool HitboxComponent::intersect(std::shared_ptr<HitboxComponent> other) {
    return hitbox.getGlobalBounds().intersects(other->hitbox.getGlobalBounds());
}

void HitboxComponent::setPosition(const sf::Vector2f &position) {
    hitbox.setPosition(position);
    sprite.setPosition(position.x - offsetX, position.y - offsetY);
}

void HitboxComponent::setPosition(float x, float y) {
    hitbox.setPosition(x, y);
    sprite.setPosition(x - offsetX, y - offsetY);
}

void HitboxComponent::setOrigin(float x, float y) {
    hitbox.setOrigin(x, y);
    sprite.setOrigin(x, y);
}
