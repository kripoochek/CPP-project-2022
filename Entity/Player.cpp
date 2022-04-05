#include "Player.h"

Player::Player(float x, float y, sf::Texture &texture) {
    initVariables();

    setTexture(texture);
    setPosition(x, y);
    sf::Vector2u size = texture.getSize();
    sprite.setOrigin(size.x / 2,size.y / 2);
    sprite.setScale(0.10f,0.10f);

    initComponents();

}

void Player::initVariables() {

}

void Player::initComponents() {
    createMovementComponent(200.f, 200.f, 200.f,  400.f);

    createHitboxComponent(sprite, 0, 0, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
}

void Player::update(float dt) {
    movementComponent->update(dt);
    hitboxComponent->update();
}

void Player::handleHitTank(std::shared_ptr<Player> other) {
    movementComponent->stop();
}

void Player::handleHitWall(std::shared_ptr<Wall> other) {
    movementComponent->stop();
}


