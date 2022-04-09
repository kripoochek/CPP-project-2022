#ifndef MY_TANKS_IN_LABIRINT_BOX_H
#define MY_TANKS_IN_LABIRINT_BOX_H

#include <vector>

#include "Wall.h"

struct Edges{
    std::shared_ptr<Wall> upper,lower,left,right;
};

class Box {
private:
    Edges edges;
    sf::Sprite sprite;
public:
    Box(sf::Vector2f coordinates,const sf::Texture& texture_);
    void setTexture(const sf::Texture& texture_);
    void setPosition(sf::Vector2f coordinates);
    void renderBox(std::shared_ptr<sf::RenderTarget> target);
    void renderEdges(std::shared_ptr<sf::RenderTarget> target);
    void deleteEdge(const std::string& posWall);
    void addEdge(const std::shared_ptr<Wall>& wall,const std::string& posWall);
    Edges getEdges() const;
    sf::Vector2f getCoordinates();
};

#endif //MY_TANKS_IN_LABIRINT_BOX_H