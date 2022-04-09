#include "Wall.h"

Wall::Wall(float x, float y, sf::Texture &texture) : hidden(false) {
    setTexture(texture);
    setPosition(x, y);

    sprite.setScale((sprite.getTexture()->getSize().x <= 100 ? 1.0 : 100.0 / sprite.getTexture()->getSize().x) ,(sprite.getTexture()->getSize().y<=100 ? 1.0 : 100.0/sprite.getTexture()->getSize().y));
    sprite.setOrigin(sprite.getTexture()->getSize().x/2,sprite.getTexture()->getSize().y/2);

    createHitboxComponent(sprite, 0, 0, sprite.getGlobalBounds().width, sprite.getGlobalBounds().height);
}

bool Wall::isHidden() const { return hidden; }

void Wall::setHidden(bool type) { hidden = type; }

void Wall::render(sf::RenderTarget& target) {
    if (!hidden) { target.draw(sprite); }
    if (hitboxComponent){ hitboxComponent->render(target); }
}
