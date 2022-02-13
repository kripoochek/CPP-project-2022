#include "DynamicObject.h"
#include "../constants.h"

void DynamicObject::setRotate(float newRotation) { sprite.setRotation(newRotation); }
void DynamicObject::setMoveSpeed(float newMoveSpeed) { moveSpeed = newMoveSpeed; }
void DynamicObject::setRotateSpeed(float newRotateSpeed) { rotateSpeed = newRotateSpeed; }
void DynamicObject::setTexture(const std::string &file) {
    texture.loadFromFile(file);
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setScale(0.1f, 0.1f);
    sprite.setOrigin(256.f, 256.f);
}


const sf::Vector2f &DynamicObject::getPosition() const { return sprite.getPosition(); }
float DynamicObject::getRotate() const { return sprite.getRotation(); }


void DynamicObject::updateRotate(bool clockwise = true) {
    float angle = (clockwise ? 1 : -1) * rotateSpeed;
    sprite.rotate(angle);
}
void DynamicObject::updatePositions(bool back) {
    float rad_angle = sprite.getRotation() * PI / 180.0;
    float dx = moveSpeed * std::cos(rad_angle);
    float dy = moveSpeed * std::sin(rad_angle);
    if (back){dx *= -1, dy *= -1;}
    sprite.move(dx, dy);
}

void DynamicObject::draw(sf::RenderWindow *window) {
    window->draw(sprite);
}







