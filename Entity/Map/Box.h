
#ifndef MY_TANKS_IN_LABIRINT_BOX_H
#define MY_TANKS_IN_LABIRINT_BOX_H

#include "Wall.h"
#include <vector>
#include <memory>
class Box {
private:
    std::vector<std::shared_ptr<Wall>> edges;
    sf::Sprite sprite;
public:
    Box(sf::Vector2f coordinates,const sf::Texture& texture_,const sf::Texture& verticalTexture,const sf::Texture& horizontalTexture);
    void setTexture(const sf::Texture& texture_);
    void setPosition(sf::Vector2f coordinates);
    void render(std::shared_ptr<sf::RenderTarget> target);
};


#endif //MY_TANKS_IN_LABIRINT_BOX_H
