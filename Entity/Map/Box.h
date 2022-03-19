
#ifndef MY_TANKS_IN_LABIRINT_BOX_H
#define MY_TANKS_IN_LABIRINT_BOX_H

#include "Wall.h"
#include <vector>
#include <memory>
#include <string>
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
    void render(std::shared_ptr<sf::RenderTarget> target);
    void deleteEdge(const std::string& posWall);
    void addEdge(const std::shared_ptr<Wall>& wall,const std::string& posWall);
    Edges getEdges();
};

#endif //MY_TANKS_IN_LABIRINT_BOX_H
