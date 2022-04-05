#ifndef MY_TANKS_IN_LABIRINT_MAP_H
#define MY_TANKS_IN_LABIRINT_MAP_H
#include <vector>
#include "Box.h"
#include "Utils.h"
class Map {
private:
    std::vector<std::vector<std::shared_ptr<Box>>> map;
public:
    int rows= randNum(5, 6); // 4 6
    int columns= randNum(8, 10); // 10
    Map(sf::Vector2f coordinates,const sf::Texture& texture_,const sf::Texture& verticalTexture,const sf::Texture& horizontalTexture);
    void render(std::shared_ptr<sf::RenderTarget> target);
    void generateMap();
    void addWalls(const sf::Texture& verticalTexture,const sf::Texture& horizontalTexture);
    std::vector<std::shared_ptr<Wall>> getActiveWalls();
};


#endif //MY_TANKS_IN_LABIRINT_MAP_H
