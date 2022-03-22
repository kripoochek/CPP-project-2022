#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(sf::Sprite& sprite, float offsetX, float offsetY, float width, float height) :
    sprite(sprite), offsetX(offsetX), offsetY(offsetY) {
    hitbox.setPosition(sprite.getPosition().x + offsetX, sprite.getPosition().y + offsetY);
    hitbox.setSize(sf::Vector2f(width, height));
    hitbox.setOrigin(width / 2, height / 2);
    hitbox.setFillColor(sf::Color::Transparent);
    hitbox.setOutlineThickness(1.f);
    hitbox.setOutlineColor(sf::Color::Green);
}

bool HitboxComponent::checkIntersect(const sf::FloatRect &frect) {
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
