#include "map.h"
#include "../constants.h"
#include "map_box.h"
#include <vector>
#include <iostream>
#include "utils.h"

Map::Map() : width(randNum(7, 13)), height(randNum(6, 8)){
};

void Map::generate() {
    boxes.resize(height, std::vector<MapBox>(width));
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            boxes[row][col] = MapBox();
        }
    }

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            if (row < height - 1) { 
                bool isWall = static_cast<bool>(randNum(0, 1));
                if (col == 0 || col == width - 1) { isWall = false; }
                else if (row == 0 || row == height - 2) { isWall = true; }

                MapBoxEdge bottomEdge({ row, col }, { row + 1, col }, isWall); 
                edges.push_back(bottomEdge);
                boxes[row][col].addEdge(edges.size() - 1);
                boxes[row + 1][col].addEdge(edges.size() - 1);
            }
            if (col < width - 1) { 
                bool isWall = static_cast<bool>(randNum(0, 1));
                if (row == 0 || row == height - 1) { isWall = false; }
                else if(col == 0 || col == width - 2) { isWall = true; }
                MapBoxEdge rightEdge({ row, col }, { row, col + 1 }, isWall); 
                edges.push_back(rightEdge);
                boxes[row][col].addEdge(edges.size() - 1);
                boxes[row][col + 1].addEdge(edges.size() - 1);
            }
        }
    }

    makeConnected();
}

void Map::makeConnected() {
    int currentComponent = -1;
    components.resize(height, std::vector<int>(width, -1));
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            if (components[row][col] == -1) {
                currentComponent++;
                dfs(row, col, -1, currentComponent);
            }
        }
    }

    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            for (auto edgeIndex : boxes[row][col].getEdges()) {
                MapBoxEdge edge = edges[edgeIndex];
                if (edge.a.first > edge.b.first || edge.a.second > edge.b.second || !edge.isWall) continue;
                if (components[edge.a.first][edge.a.second] == 0 || components[edge.b.first][edge.b.second] == 0) continue;
                if (components[edge.a.first][edge.a.second] != components[edge.b.first][edge.b.second]) {
                    edges[edgeIndex].isWall = false;
                    dfs(edge.b.first, edge.b.second, components[edge.b.first][edge.b.second], components[edge.a.first][edge.a.second]);
                }
            }
        }
    }
}

void Map::dfs(int row, int column, int oldComponent, int newComponent) {
    components[row][column] = newComponent;
    MapBox box = boxes[row][column];
    for (int edgeIndex : box.getEdges()) {
        MapBoxEdge edge = edges[edgeIndex];
        if (!edge.isWall) { 
            if (components[edge.a.first][edge.a.second] == oldComponent) dfs(edge.a.first, edge.a.second, oldComponent, newComponent);
            if (components[edge.b.first][edge.b.second] == oldComponent) dfs(edge.b.first, edge.b.second, oldComponent, newComponent);
        }
    }
}

int Map::getWidth() {
    return width;
}

int Map::getHeight() {
    return height;
}

void Map::setTheme(Theme* newTheme) {
    theme = newTheme;
}

void Map::draw(sf::RenderTexture& window) {
    float xCorner = (window.getSize().x - (width * MAP_BOX_SIZE)) / 2;
    float yCorner = (window.getSize().y - (height * MAP_BOX_SIZE)) / 2;
    for (int row = 0; row < height; row++) {
        for (int col = 0; col < width; col++) {
            boxes[row][col].setCorner(xCorner, yCorner);
            sf::RectangleShape boxView;
            boxView.setSize(sf::Vector2f(MAP_BOX_SIZE, MAP_BOX_SIZE));
            boxView.setPosition(xCorner, yCorner);
            if (row == 0 || row == height - 1 || col == 0 || col == width - 1) {
                boxView.setFillColor(sf::Color{0xf0efedFF});
            } else {
                theme->applyBox(boxView);
            }
            window.draw(boxView);
            xCorner += MAP_BOX_SIZE;
        }
        yCorner += MAP_BOX_SIZE;
        xCorner = (window.getSize().x - (width * MAP_BOX_SIZE)) / 2;
    }

    int count = 0;
    for (auto mapBoxEdge : edges) {        
        // top/bottom wall
        if (mapBoxEdge.isWall && mapBoxEdge.a.second == mapBoxEdge.b.second && count < 32) {
            count++;
            MapBox topBox = boxes[mapBoxEdge.a.first][mapBoxEdge.a.second];
            MapBox bottomBox = boxes[mapBoxEdge.b.first][mapBoxEdge.b.second];
            sf::RectangleShape wallView;
            wallView.setSize(sf::Vector2f(MAP_BOX_SIZE, WALL_THICKNESS));
            wallView.setPosition(topBox.getCornerX(), bottomBox.getCornerY() - (WALL_THICKNESS / 2));
            theme->applyWall(wallView);
            window.draw(wallView);
        }
        // left/right wall
        if (mapBoxEdge.isWall && mapBoxEdge.a.first == mapBoxEdge.b.first) {  
            MapBox leftBox = boxes[mapBoxEdge.a.first][mapBoxEdge.a.second];
            MapBox rightBox = boxes[mapBoxEdge.b.first][mapBoxEdge.b.second];
            sf::RectangleShape wallView;
            wallView.setSize(sf::Vector2f(WALL_THICKNESS, MAP_BOX_SIZE));
            wallView.setPosition(rightBox.getCornerX() - (WALL_THICKNESS / 2), leftBox.getCornerY());
            theme->applyWall(wallView);
            window.draw(wallView);
        }
    }
}

std::vector<std::vector<MapBox>> &Map::getBoxes() {
    return boxes;
}

std::vector<MapBoxEdge> &Map::getEdges() {
    return edges;
}