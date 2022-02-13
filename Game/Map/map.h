#ifndef MAP_H_
#define MAP_H_

#include <SFML/Graphics.hpp>
#include "map_box.h"
#include "theme.h"
#include <vector>

class Map {
private:
    int width, height;
    Theme* theme;
    std::vector<std::vector<MapBox>> boxes;
    std::vector<std::vector<int>> components;
    std::vector<MapBoxEdge> edges;
    public:
        Map();
        void generate();
        void makeConnected();
        void generateEdges();
        void dfs(int row, int column, int oldComponent, int newComponent);
        int getWidth();
        void draw(sf::RenderTexture& window);
        void setTheme(Theme* newTheme);
        int getHeight();
        std::vector<std::vector<MapBox>> &getBoxes();
        std::vector<MapBoxEdge> &getEdges();
};
#endif