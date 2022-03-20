#include "Player.h"

Player::Player(float x, float y, sf::Texture &texture) {
    initVariables();
    initComponents();

    setTexture(texture);
    setPosition(x, y);

    sf::Vector2u size = texture.getSize();
    sprite.setOrigin(size.x / 2,size.y / 2);
    sprite.setScale(0.10f,0.10f);
}

void Player::initVariables() {

}

void Player::initComponents() {
    createMovementComponent(200.f, 200.f, 200.f,  400.f);
}
