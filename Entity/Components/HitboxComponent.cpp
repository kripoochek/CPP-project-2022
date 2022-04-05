#include "HitboxComponent.h"

HitboxComponent::HitboxComponent(sf::Sprite& sprite, float offsetX, float offsetY, float width, float height) :
    sprite(sprite), offsetX(offsetX), offsetY(offsetY) {
    hitboxShape.setPosition(sprite.getPosition().x + offsetX, sprite.getPosition().y + offsetY);
    hitboxShape.setSize(sf::Vector2f(width, height));
    hitboxShape.setOrigin(width / 2, height / 2);
    hitboxShape.setFillColor(sf::Color::Transparent);
    hitboxShape.setOutlineThickness(1.f);
    hitboxShape.setOutlineColor(sf::Color::Green);
}

bool HitboxComponent::checkIntersect(const sf::FloatRect &frect) {
    return sprite.getGlobalBounds().intersects(frect);
}

void HitboxComponent::update() {
    hitboxShape.setPosition(sprite.getPosition().x + offsetX, sprite.getPosition().y + offsetY);
    hitboxShape.setRotation(sprite.getRotation());
}

void HitboxComponent::render(sf::RenderTarget &target) {
//    target.draw(hitboxShape);
}

sf::FloatRect HitboxComponent::getGlobalBounds() const {
    return hitboxShape.getGlobalBounds();
}

bool HitboxComponent::intersect(std::shared_ptr<HitboxComponent> other) {
    return hitboxShape.getGlobalBounds().intersects(other->hitboxShape.getGlobalBounds());
}
