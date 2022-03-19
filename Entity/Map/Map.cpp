
#include "Map.h"

bool checkerBorders(const std::pair<int, int> &p, const int &step, const int &h, const int &w) {
    if (p.first == 0 and step == 0) return false;
    if (p.first == h - 1 and step == 1) return false;
    if (p.first == 0 and step == 2) return false;
    if (p.first == w - 1 and step == 3) return false;
    return true;
}

void
addAvailable(const std::pair<int, int> current, std::vector<std::pair<int, int>> &availableBoxes, int height, int witdh,
             const std::vector<std::vector<bool>> &used) {
    if (checkerBorders({current.first - 1, current.second}, 0, height, witdh) and
        !used[current.first - 1][current.second]) {
        availableBoxes.push_back({current.first - 1, current.second});
    }
    if (checkerBorders({current.first + 1, current.second}, 1, height, witdh) and
        !used[current.first + 1][current.second]) {
        availableBoxes.push_back({current.first + 1, current.second});
    }
    if (checkerBorders({current.first, current.second - 1}, 2, height, witdh) and
        !used[current.first][current.second - 1]) {
        availableBoxes.push_back({current.first, current.second - 1});
    }
    if (checkerBorders({current.first, current.second + 1}, 3, height, witdh) and
        !used[current.first][current.second + 1]) {
        availableBoxes.push_back({current.first, current.second + 1});
    }
}

std::pair<int, int> getCommonBorder(const std::pair<int, int> &from, const std::pair<int, int> &to) {
    if ((to.first - from.first) == 1) return {1, 0};
    if ((to.first - from.first) == -1) return {0, 1};
    if ((to.second - from.second) == 1) return {3, 2};
    if ((to.second - from.second) == -1) return {2, 3};
}

Map::Map(sf::Vector2f coordinates, const sf::Texture &texture_, const sf::Texture &verticalTexture,
         const sf::Texture &horizontalTexture) {
    for (int i = 0; i < height; i++) {
        sf::Vector2f rowcoor = coordinates;
        map.push_back(std::vector<std::shared_ptr<Box>>{
                std::make_shared<Box>(coordinates, texture_)});
        coordinates = sf::Vector2f(coordinates.x, coordinates.y + 100);
        for (int j = 1; j < witdh; j++) {
            map[i].push_back(std::make_shared<Box>(rowcoor, texture_));
            rowcoor = sf::Vector2f(rowcoor.x + 100, rowcoor.y);
        }
    }
    addWalls(verticalTexture,horizontalTexture);
    generateMap();
}

void Map::addWalls( const sf::Texture &verticalTexture,
                   const sf::Texture &horizontalTexture) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < witdh; j++) {
            /*
            std::shared_ptr<Wall> upper=std::make_shared<Wall>(sf::Vector2f(coordinates.x,coordinates.y-50),horizontalTexture);
            std::shared_ptr<Wall> lower=std::make_shared<Wall>(sf::Vector2f(coordinates.x,coordinates.y+50),horizontalTexture);
            std::shared_ptr<Wall> right=std::make_shared<Wall>(sf::Vector2f(coordinates.x+50,coordinates.y),horizontalTexture);
            std::shared_ptr<Wall> left=std::make_shared<Wall>(sf::Vector2f(coordinates.x-50,coordinates.y),horizontalTexture);*/
            Edges edges=map[i][j]->getEdges();
            if (edges.upper== nullptr){
                std::shared_ptr<Wall> upper=std::make_shared<Wall>(sf::Vector2f(map[i][j],coordinates.y-50),horizontalTexture);
                map[i][j]->addEdge(upper,"upper");
                if (i-1>=0){
                    map[i-1][j]->addEdge(upper,"lower");
                }
            }
            if (edges.lower== nullptr){
                std::shared_ptr<Wall> lower=std::make_shared<Wall>(sf::Vector2f(coordinates.x,coordinates.y+50),horizontalTexture);
                map[i][j]->addEdge(lower,"lower");
                if (i+1<height){
                    map[i+1][j]->addEdge(lower,"upper");
                }
            }
            if (edges.left== nullptr){
                std::shared_ptr<Wall> left=std::make_shared<Wall>(sf::Vector2f(coordinates.x-50,coordinates.y),verticalTexture);
                map[i][j]->addEdge(left,"left");
                if (j-1>=0){
                    map[i][j-1]->addEdge(left,"right");
                }
            }
            if (edges.upper== nullptr){
                std::shared_ptr<Wall> right=std::make_shared<Wall>(sf::Vector2f(coordinates.x+50,coordinates.y),verticalTexture);
                map[i][j]->addEdge(right,"right");
                if (j+1<witdh){
                    map[i][j+1]->addEdge(right,"left");
                }
            }
        }
    }

}

void Map::render(std::shared_ptr<sf::RenderTarget> target) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < witdh; j++) {
            map[i][j]->render(target);
        }
    }
}

void Map::generateMap() {
}