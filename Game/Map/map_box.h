#ifndef MAP_BOX_H_
#define MAP_BOX_H_

#include <vector>
#include <SFML/Graphics.hpp>

struct MapBoxEdge {
    const std::pair<int, int> a;
    const std::pair<int, int> b;
    bool isWall;
    MapBoxEdge(std::pair<int, int> a, std::pair<int, int> b, bool isWall);
};

class MapBox {
    std::vector<int> edges;
    float cornerX, cornerY;
    public:
        MapBox();
        void addEdge(int edgeIndex);
        std::vector<int> getEdges();
        void setCorner(float x, float y);
        float getCornerX();
        float getCornerY();
};
#endif