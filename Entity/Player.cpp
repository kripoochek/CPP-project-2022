#include "Player.h"

Player::Player(float x, float y, sf::Texture &texture) {
    initVariables();
    initComponents();

    setTexture(texture);
    setPosition(x, y);
}

void Player::initVariables() {

}

void Player::initComponents() {
    createMovementComponent(100.f);
}
