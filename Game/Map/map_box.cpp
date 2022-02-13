#include <SFML/Graphics.hpp>
#include <vector>
#include "map_box.h"
#include "../constants.h"
#include "utils.h"

void MapBox::setCorner(float x, float y) {
    cornerX = x;
    cornerY = y;
}

float MapBox::getCornerX() {
    return cornerX;
}

float MapBox::getCornerY() {
    return cornerY;
}
std::vector<int> MapBox::getEdges() {
    return edges;
}

MapBox::MapBox() {
};

void MapBox::addEdge(int edgeIndex) {
    edges.push_back(edgeIndex);
}

MapBoxEdge::MapBoxEdge(std::pair<int, int> a, std::pair<int, int> b, bool isWall) : a(a), b(b), isWall(isWall){
};