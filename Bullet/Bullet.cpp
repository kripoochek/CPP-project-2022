#include "Bullet.h"

Bullet::Bullet(float x, float y, float angle, float lifeTime, sf::Texture &texture) : lifeTime(std::chrono::duration<double>(lifeTime)) {
    initVariables();

    texture.setSmooth(true);
    this->setTexture(texture);
    this->setPosition(x, y);

    sf::Vector2u size = texture.getSize();
    sprite.setOrigin(size.x / 2,size.y / 2);
    sprite.setScale(0.05f,0.05f);
    sprite.setRotation(angle);
    initTime = std::chrono::system_clock::now();

    initComponents();
}

void Bullet::initVariables() {

}

bool Bullet::isDeathTime() {
    auto currentTime = std::chrono::system_clock::now();
    std::chrono::duration<double> currentInterval = currentTime - initTime;
    return (currentInterval >= lifeTime);
}

void Bullet::initComponents() {
    createMovementComponent(200.f, 200.f, 200.f, 200.f,  0);
    createHitboxComponent(sprite, 0, 0, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
}