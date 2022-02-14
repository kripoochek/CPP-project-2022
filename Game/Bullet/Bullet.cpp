#include "Bullet.h"
namespace Bullet {

    const sf::Vector2f &Bullet::getPosition() const { return sprite.getPosition(); }

    void Bullet::setDirection(float newDirection) {
        direction = newDirection;
        sprite.setRotation(direction);
    }

    void Bullet::setLifeTime(int newLifeTime) {
        lifeTime = newLifeTime;
    }

    void Bullet::setMoveSpeed(float newMoveSpeed) {
        moveSpeed = newMoveSpeed;
    }

    void Bullet::draw(sf::RenderWindow *window) {
        window->draw(sprite);
    }

    void Bullet::updatePositions() {
        lifeTime--;
        float rad_angle = sprite.getRotation() * PI / 180.0;
        float dx = moveSpeed * std::cos(rad_angle);
        float dy = moveSpeed * std::sin(rad_angle);
        sprite.move(dx, dy);
    }

    int Bullet::getLifeTime() {
        return lifeTime;
    }
    void Bullet::setTexture(const std::string &file) {
        texture.loadFromFile(file);
        texture.setSmooth(true);
        sprite.setTexture(texture);
        sprite.setScale(0.1f, 0.1f);
        sprite.setOrigin(256.f, 256.f);

    }
}