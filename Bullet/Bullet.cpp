/*#include "Bullet.h"
#include <iostream>
namespace Bullet {
    Bullet::Bullet(const float &direction, const float &x, const float &y, const int &lifetime) {
        setDirection(direction);
        setStartPosition(x,y);
        setLifeTime(lifetime);
    }
    Bullet::Bullet() {
        setStartPosition(50,50);
    }
    void Bullet::setDirection(float newDirection) {
        direction = newDirection;
        sprite.setRotation(direction);
    }

    void Bullet::setLifeTime(int newLifeTime) {
        lifeTime = newLifeTime;
    }

    void Bullet::draw(sf::RenderWindow *window) {
        if (lifeTime > 0) window->draw(sprite);
    }

    void Bullet::updatePositions() {
        setDirection(60);
        this->lifeTime--;
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
        sprite.setScale(0.03f, 0.03f);
        sprite.setOrigin(256.f, 256.f);

    }
    void Bullet::setStartPosition(const float &x, const float &y) {
        this->sprite.setPosition(x,y);
    }
}*/