
#ifndef MY_TANKS_IN_LABIRINT_MAP_H
#define MY_TANKS_IN_LABIRINT_MAP_H

#include <vector>
#include "Box.h"
#include "utils.h"
class Map {
private:
    std::vector<std::vector<std::shared_ptr<Box>>> map;
public:
    int height= randNum(4,6);
    int witdh= randNum(10,10);
    Map(sf::Vector2f coordinates,const sf::Texture& texture_,const sf::Texture& verticalTexture,const sf::Texture& horizontalTexture);
    void render(std::shared_ptr<sf::RenderTarget> target);
    void generateMap();
    void addWalls(const sf::Texture& verticalTexture,const sf::Texture& horizontalTexture);

};


#endif //MY_TANKS_IN_LABIRINT_MAP_H
