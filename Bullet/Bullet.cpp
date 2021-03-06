#include "Bullet.h"

Bullet::Bullet(std::shared_ptr<b2World> world, float x, float y, float angle, float lifeTime, sf::Texture &texture) : lifeTime(std::chrono::duration<double>(lifeTime)) {

    initTime = std::chrono::system_clock::now();
    initSFML(x, y, angle, texture);
    initBox2D(world);

    initComponents();
    sf::Vector2f velocity;
    velocity.x = std::cos(sprite.getRotation() * (3.1415f / 180)) * 5.0f;
    velocity.y = std::sin(sprite.getRotation() * (3.1415f / 180)) * 5.0f;
    body->SetLinearVelocity(b2Vec2(velocity.x, velocity.y));
}

bool Bullet::isDeathTime() {
    auto currentTime = std::chrono::system_clock::now();
    std::chrono::duration<double> currentInterval = currentTime - initTime;
    return (currentInterval >= lifeTime);
}

void Bullet::initComponents() {

    createHitboxComponent(sprite, 0, 0, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
}

void Bullet::initSFML(float x, float y, float angle, sf::Texture &texture) {
    texture.setSmooth(true);
    this->setTexture(texture);
    this->setPosition(x, y);

    sf::Vector2u size = texture.getSize();
    sprite.setOrigin(size.x / 2,size.y / 2);
    sprite.setScale(0.03f,0.03f);
    sprite.setRotation(angle);
}

void Bullet::initBox2D(std::shared_ptr<b2World> initWorld) {
    world = initWorld;

    bodyDef = std::make_shared<b2BodyDef>();
    bodyDef->type = b2_dynamicBody;
    bodyDef->position.Set(this->getPosition().x / SCALE, this->getPosition().y / SCALE);

    body = world->CreateBody(bodyDef.get());

    shape = std::make_shared<b2CircleShape>();
    auto size = sprite.getGlobalBounds();
    shape->m_radius=size.height/2/SCALE;

    fixtureDef = std::make_shared<b2FixtureDef>();
    fixtureDef->shape = shape.get();
    fixtureDef->density = 1.0f;
    fixtureDef->friction = 0;
    fixtureDef->restitution = 1.0f;
    body->CreateFixture(fixtureDef.get());
}


