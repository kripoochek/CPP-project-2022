#include "Wall.h"

Wall::Wall(std::shared_ptr<b2World> world, float x, float y, sf::Texture &texture) : hidden(false) {
    initSFML(x, y, texture);
    initBox2D(world);
    initComponents();

}

bool Wall::isHidden() const { return hidden; }

void Wall::setHidden(bool type) {
    hidden = type;
    world->DestroyBody(body);
}

void Wall::render(sf::RenderTarget &target) {
    if (!hidden) { target.draw(sprite); }
    if (hitboxComponent) { hitboxComponent->render(target); }
}

void Wall::initSFML(float x, float y, sf::Texture &texture) {
    setTexture(texture);
    setPosition(x, y);

    sprite.setScale((sprite.getTexture()->getSize().x <= 100 ? 1.0 : 100.0 / sprite.getTexture()->getSize().x),
                    (sprite.getTexture()->getSize().y <= 100 ? 1.0 : 100.0 / sprite.getTexture()->getSize().y));
    sprite.setOrigin(sprite.getTexture()->getSize().x / 2, sprite.getTexture()->getSize().y / 2);
}

void Wall::initBox2D(std::shared_ptr<b2World> initWorld) {
    world = initWorld;

    bodyDef = std::make_shared<b2BodyDef>();
    bodyDef->type = b2_staticBody;
    bodyDef->position.Set(sprite.getPosition().x / SCALE, sprite.getPosition().y / SCALE);

    body = world->CreateBody(bodyDef.get());

    shape = std::make_shared<b2PolygonShape>();
    auto size = sprite.getGlobalBounds();
    shape->SetAsBox(size.width / 2 / SCALE, size.height / 2 / SCALE);

    fixtureDef = std::make_shared<b2FixtureDef>();
    fixtureDef->shape = shape.get();
    fixtureDef->friction = 0;
    body->CreateFixture(shape.get(), 0);
}


void Wall::initComponents() {
    createHitboxComponent(sprite, 0, 0, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
}
