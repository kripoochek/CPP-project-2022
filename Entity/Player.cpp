#include "Player.h"

Player::Player(float x, float y, sf::Texture &texture) {
    initVariables();
    initComponents();

    setTexture(texture);
    setPosition(x, y);
    this->sprite.setOrigin(256,200);
}

void Player::initVariables() {

}

void Player::initComponents() {
    createMovementComponent(1000.f, 100.f);
}
