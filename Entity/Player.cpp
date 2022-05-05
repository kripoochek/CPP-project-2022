#include "Player.h"

Player::Player(std::shared_ptr<b2World> world,
               float x,
               float y,
               int maxBulletCount,
               int id,
               sf::Texture &texture)
    : id(id), bulletCount(maxBulletCount) {
    intervalNewAttack = std::chrono::duration<double>(0.20);
    initSFML(x, y, texture);
    initBox2D(world);
    initComponents();
}

void Player::initComponents() {
    createMovementComponent(200.f, 200.f, 0, 200.f, 400.f);
    createHitboxComponent(sprite, 0, 0, sprite.getGlobalBounds().width,
                          sprite.getGlobalBounds().height);
}

void Player::attack(
    std::deque<std::pair<int, std::shared_ptr<Bullet>>> &bullets,
    sf::Texture &texture,
    float dt) {
    auto currentTime = std::chrono::system_clock::now();
    std::chrono::duration<double> currentInterval =
        currentTime - lastAttackCommandTime;
    if (currentInterval < intervalNewAttack || bulletCount == 0) {
        return;
    }
    lastAttackCommandTime = std::chrono::system_clock::now();
    bulletCount--;
    bullets.emplace_back(id, std::make_shared<Bullet>(
                                 world, sprite.getPosition().x, sprite.getPosition().y,
                                 sprite.getRotation(), 2, texture));
}

void Player::addBullet() { bulletCount++; }

void Player::initSFML(float x, float y, sf::Texture &texture) {
    setTexture(texture);
    setPosition(x, y);
    sf::Vector2u size = texture.getSize();
    sprite.setOrigin(size.x / 2, size.y / 2);
    sprite.setScale(0.10f, 0.10f);
}

void Player::initBox2D(std::shared_ptr<b2World> initWorld) {
    world = initWorld;

    bodyDef = std::make_shared<b2BodyDef>();
    bodyDef->type = b2_dynamicBody;
    bodyDef->position.Set(sprite.getPosition().x / SCALE, sprite.getPosition().y / SCALE);

    body = world->CreateBody(bodyDef.get());

    shape = std::make_shared<b2PolygonShape>();
    auto size = sprite.getGlobalBounds();
    shape->SetAsBox(size.width / 2 / SCALE - b2_polygonRadius,  size.height / 2 / SCALE - b2_polygonRadius);

    fixtureDef = std::make_shared<b2FixtureDef>();
    fixtureDef->shape = shape.get();
    fixtureDef->density = 1.0f;
    fixtureDef->friction = 0.3f;
    body->CreateFixture(fixtureDef.get());
}

