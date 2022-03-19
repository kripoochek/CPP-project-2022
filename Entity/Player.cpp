#include "Player.h"

Player::Player(float x, float y, sf::Texture &texture) {
    initVariables();
    initComponents();

    setTexture(texture);
    setPosition(x, y);
    sprite.setOrigin(512/2,397/2);
    sprite.setScale(0.10,0.10);
}

void Player::initVariables() {

}

void Player::initComponents() {
    createMovementComponent(700.f, 500.f);
}
