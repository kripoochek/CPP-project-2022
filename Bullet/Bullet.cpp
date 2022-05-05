#include "Bullet.h"

Bullet::Bullet(std::shared_ptr<b2World> world, float x, float y, float angle, float lifeTime, sf::Texture &texture) : lifeTime(std::chrono::duration<double>(lifeTime)) {

    initTime = std::chrono::system_clock::now();
    initSFML(x, y, angle, texture);
    initBox2D(world);

    initComponents();
}

bool Bullet::isDeathTime() {
    auto currentTime = std::chrono::system_clock::now();
    std::chrono::duration<double> currentInterval = currentTime - initTime;
    return (currentInterval >= lifeTime);
}

void Bullet::initComponents() {
    createMovementComponent(200.f, 200.f, 200.f, 200.f,  0);
    createHitboxComponent(sprite, 0, 0, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
}

void Bullet::initSFML(float x, float y, float angle, sf::Texture &texture) {
    texture.setSmooth(true);
    this->setTexture(texture);
    this->setPosition(x, y);

    sf::Vector2u size = texture.getSize();
    sprite.setOrigin(size.x / 2,size.y / 2);
    sprite.setScale(0.05f,0.05f);
    sprite.setRotation(angle);
}

void Bullet::initBox2D(std::shared_ptr<b2World> initWorld) {
    world = initWorld;

    bodyDef = std::make_shared<b2BodyDef>();
    bodyDef->type = b2_dynamicBody;
    bodyDef->position.Set(this->getPosition().x / SCALE, this->getPosition().y / SCALE);

    body = world->CreateBody(bodyDef.get());

    shape = std::make_shared<b2PolygonShape>();
    auto size = sprite.getGlobalBounds();
    shape->SetAsBox(size.width / 2 / SCALE,  size.height / 2 / SCALE);

    fixtureDef = std::make_shared<b2FixtureDef>();
    fixtureDef->shape = shape.get();
    fixtureDef->density = 1.0f;
    fixtureDef->friction = 0.3f;
    body->CreateFixture(fixtureDef.get());
}


