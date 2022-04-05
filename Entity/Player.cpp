#include "Player.h"

Player::Player(float x, float y, sf::Texture &texture){
    initVariables();

    setTexture(texture);
    setPosition(x, y);
    sf::Vector2u size = texture.getSize();
    sprite.setOrigin(size.x / 2,size.y / 2);
    sprite.setScale(0.10f,0.10f);
    intervalNewAttack = std::chrono::duration<double>(0.20);
    initComponents();
}

void Player::initVariables() {

}

void Player::initComponents() {
    createMovementComponent(200.f, 200.f, 0,200.f,  400.f);

    createHitboxComponent(sprite, 0, 0, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
}


void Player::handleHitTank(std::shared_ptr<Player> other) {
    movementComponent->stop();
}

void Player::handleHitWall(std::shared_ptr<Wall> other) {
    movementComponent->stop();
}

void Player::attack(std::deque<std::shared_ptr<Bullet>> &bullets, sf::Texture &texture, float dt) {
    auto currentTime = std::chrono::system_clock::now();
    std::chrono::duration<double> currentInterval = currentTime - lastAttackCommandTime;
    if (currentInterval < intervalNewAttack) { return; }
    lastAttackCommandTime = std::chrono::system_clock::now();
    bullets.push_back(std::make_shared<Bullet>(sprite.getPosition().x, sprite.getPosition().y,
                                               sprite.getRotation(), 2, texture));
}