#include "Player.h"

Player::Player(float x, float y, sf::Texture &texture) {
    this->initVariables();
    this->initComponents();

    this->setTexture(texture);
    this->setPosition(x, y);
    sprite.setOrigin(546.f/2,546.f/2);
    sprite.setScale(0.10f,0.10f);
}

void Player::initVariables() {

}

void Player::initComponents() {
    createMovementComponent(400.f, 360.f);
}
