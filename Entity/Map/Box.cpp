#include "Box.h"
Box::Box(sf::Vector2f coordinates, const sf::Texture &texture_,const sf::Texture& verticalTexture,const sf::Texture& horizontalTexture) {
    setTexture(texture_);
    setPosition(coordinates);
    edges.push_back(std::make_shared<Wall>(coordinates,horizontalTexture,true));
    edges.push_back(std::make_shared<Wall>(coordinates,verticalTexture,false));
    edges.push_back(std::make_shared<Wall>(sf::Vector2f(coordinates.x,coordinates.y+sprite.getScale().y),horizontalTexture,true));
    edges.push_back(std::make_shared<Wall>(sf::Vector2f(coordinates.x+sprite.getScale().x,coordinates.y),verticalTexture,false));
}

void Box::setPosition(sf::Vector2f coordinates) {
    sprite.setPosition(coordinates);
}

void Box::setTexture(const sf::Texture &texture_) {
    sprite.setTexture(texture_);
}

void Box::render(std::shared_ptr<sf::RenderTarget> target) {
    target->draw(sprite);
    for (auto edge:edges){
        edge->render(target);
    }
}
