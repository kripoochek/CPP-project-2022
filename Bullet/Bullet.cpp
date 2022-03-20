#include "Bullet.h"

Bullet::Bullet(float x, float y, float lifeTime, sf::Texture &texture) : lifeTime(lifeTime) {
    initVariables();
    initComponents();

    texture.setSmooth(true);
    this->setTexture(texture);
    this->setPosition(x, y);

    sf::Vector2u size = texture.getSize();
    sprite.setOrigin(size.x / 2,size.y / 2);
    sprite.setScale(0.05f,0.05f);
}

void Bullet::initVariables() {

}

void Bullet::initComponents() {
    createMovementComponent(200.f, 200.f, 200.f,  400.f);
}