
#include "Map.h"
bool checkerBorders(const std::pair<int,int>& p,const std::vector<std::vector<bool>> &used,int height, int witdh){
    return (p.first>=0 && p.first<height && p.second>=0 && p.second<witdh && !used[p.first][p.second]);
}

void
addAvailable(const std::pair<int, int>& current, std::vector<std::pair<std::pair<int,int>,std::string>>& availableBoxes, int height, int witdh,std::vector<std::vector<bool>> &used) {
    if (checkerBorders({current.first+1,current.second},used,height,witdh)){
        used[current.first+1][current.second]=true;
        availableBoxes.push_back({{current.first+1,current.second},"upper"});
    }
    if (checkerBorders({current.first-1,current.second},used,height,witdh)){
        used[current.first-1][current.second]=true;
        availableBoxes.push_back({{current.first-1,current.second},"lower"});
    }
    if (checkerBorders({current.first,current.second+1},used,height,witdh)){
        used[current.first][current.second+1]=true;

        availableBoxes.push_back({{current.first,current.second+1},"left"});
    }
    if (checkerBorders({current.first,current.second-1},used,height,witdh)){
        used[current.first][current.second-1]=true;

        availableBoxes.push_back({{current.first,current.second-1},"right"});
    }
}


Map::Map(sf::Vector2f coordinates, const sf::Texture &texture_, const sf::Texture &verticalTexture,
         const sf::Texture &horizontalTexture) {
    for (int i = 0; i < height; i++) {
        map.push_back(std::vector<std::shared_ptr<Box>>{
                std::make_shared<Box>(coordinates, texture_)});
        coordinates = sf::Vector2f(coordinates.x, coordinates.y + 100);
        sf::Vector2f rowCoor=sf::Vector2f(coordinates.x+100,coordinates.y-100);
        for (int j = 0; j < witdh; j++) {
            map[i].push_back(std::make_shared<Box>(rowCoor, texture_));
            rowCoor = sf::Vector2f(rowCoor.x + 100, rowCoor.y);
        }
    }
    addWalls(verticalTexture,horizontalTexture);
    generateMap();
}

void Map::addWalls( const sf::Texture &verticalTexture,
                   const sf::Texture &horizontalTexture) {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < witdh; j++) {
            Edges edges=map[i][j]->getEdges();
            if (edges.upper== nullptr){
                std::shared_ptr<Wall> upper=std::make_shared<Wall>(sf::Vector2f(map[i][j]->getCoordinates().x,map[i][j]->getCoordinates().y-50),horizontalTexture);
                map[i][j]->addEdge(upper,"upper");
                if (i-1>=0){
                    map[i-1][j]->addEdge(upper,"lower");
                }
            }
            if (edges.lower== nullptr){
                std::shared_ptr<Wall> lower=std::make_shared<Wall>(sf::Vector2f(map[i][j]->getCoordinates().x,map[i][j]->getCoordinates().y+50),horizontalTexture);
                map[i][j]->addEdge(lower,"lower");
                if (i+1<height){
                    map[i+1][j]->addEdge(lower,"upper");
                }
            }
            if (edges.left== nullptr){
                std::shared_ptr<Wall> left=std::make_shared<Wall>(sf::Vector2f(map[i][j]->getCoordinates().x-50,map[i][j]->getCoordinates().y),verticalTexture);
                map[i][j]->addEdge(left,"left");
                if (j-1>=0){
                    map[i][j-1]->addEdge(left,"right");
                }
            }
            if (edges.right== nullptr){
                std::shared_ptr<Wall> right=std::make_shared<Wall>(sf::Vector2f(map[i][j]->getCoordinates().x+50,map[i][j]->getCoordinates().y),verticalTexture);
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
            map[i][j]->renderBox(target);
        }
    }
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < witdh; j++) {
            map[i][j]->renderEdges(target);
        }
    }
}

void Map::generateMap() {
    std::vector<std::pair<std::pair<int,int>,std::string>> availableBoxes;
    std::vector<std::vector<bool>> used(height,std::vector<bool>(witdh,false));
    std::pair<int,int> from={randNum(0,height-1), randNum(0,witdh-1)};
    used[from.first][from.second]=true;
    addAvailable(from,availableBoxes,height,witdh,used);
    int cntMark=1;
    int save=0;
    while (cntMark!=witdh*height ){
        int indx= randNum(0,static_cast<int>(availableBoxes.size())-1);
        std::pair<std::pair<int,int>,std::string> currBox=availableBoxes[indx];
        map[currBox.first.first][currBox.first.second]->deleteEdge(currBox.second);
        used[currBox.first.first][currBox.first.second];
        swap(availableBoxes[indx],availableBoxes[availableBoxes.size()-1]);
        availableBoxes.pop_back();
        addAvailable({currBox.first.first,currBox.first.second},availableBoxes,height,witdh,used);
        cntMark++;
        save++;
    }
}