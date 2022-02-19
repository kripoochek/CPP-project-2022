#include "Tank.h"

Tank::Tank(float x, float y, const std::string &file) {
    setTexture(file);
    sprite.setPosition(x, y);
}

void Tank::setTexture(const std::string &file) {
    texture.loadFromFile(file);
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setScale(0.1f, 0.1f);
    sprite.setOrigin(256.f, 256.f);
}

bool Tank::intersects(Tank &other) {
    return sprite.getGlobalBounds().intersects(other.sprite.getGlobalBounds());
}
