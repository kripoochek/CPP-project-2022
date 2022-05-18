#include "Player.h"

Player::Player(float x, float y, int maxBulletCount, int id, sf::Texture &texture) : id(id), bulletCount(maxBulletCount) {
    initVariables();

    setTexture(texture);
    setPosition(x, y);
    sf::Vector2u size = texture.getSize();
    sprite.setOrigin(size.x / 2, size.y / 2);
    sprite.setScale(0.10f,0.10f);
    intervalNewAttack = std::chrono::duration<double>(0.20);
    initComponents();
}

int Player::getId() {
    return id;
}

void Player::initVariables() {

}

void Player::initComponents() {
    createMovementComponent(200.f, 200.f, 0,200.f,  400.f);

    createHitboxComponent(sprite, 0, 0, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
}

void Player::attack(std::deque<std::pair<int, std::shared_ptr<Bullet>>> &bullets, sf::Texture &texture, float dt) {
    auto currentTime = std::chrono::system_clock::now();
    std::chrono::duration<double> currentInterval = currentTime - lastAttackCommandTime;
    if (currentInterval < intervalNewAttack || bulletCount == 0) { return; }
    lastAttackCommandTime = std::chrono::system_clock::now();
    bulletCount--;
    bullets.emplace_back(id, std::make_shared<Bullet>(sprite.getPosition().x, sprite.getPosition().y,
                                               sprite.getRotation(), 2, texture));
}

void Player::addBullet() { bulletCount++; }
