#ifndef MY_TANKS_IN_LABIRINT_MAP_H
#define MY_TANKS_IN_LABIRINT_MAP_H

#include <vector>

#include "Box.h"
#include "../../Utils.h"

struct Map {
    Map(std::shared_ptr<b2World> world, sf::Vector2f coordinates, sf::Texture& texture_, sf::Texture& verticalTexture, sf::Texture& horizontalTexture);

    int rows = randNum(5, 6); // 4 6
    int columns = randNum(8, 10); // 10
    void render(std::shared_ptr<sf::RenderTarget> target);
    void generateMap();
    void addWalls(sf::Texture& verticalTexture, sf::Texture& horizontalTexture);
    std::vector<std::shared_ptr<Wall>> getActiveWalls();
private:
    std::vector<std::vector<std::shared_ptr<Box>>> map;
    std::shared_ptr<b2World> world;
};


#endif //MY_TANKS_IN_LABIRINT_MAP_H
