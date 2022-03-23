#include "Box.h"
Box::Box(sf::Vector2f coordinates, const sf::Texture &texture_) {
    setTexture(texture_);
    setPosition(coordinates);
    sprite.setScale(100.0/512,100.0/512);

}

void Box::setPosition(sf::Vector2f coordinates) {
    sprite.setPosition(coordinates);
}

void Box::setTexture(const sf::Texture &texture_) {
    sprite.setTexture(texture_);
}

void Box::renderBox(std::shared_ptr<sf::RenderTarget> target) {
    target->draw(sprite);
}

void Box::renderEdges(std::shared_ptr<sf::RenderTarget> target) {
    if (edges.upper!= nullptr){
        edges.upper->render(*target);
    }
    if (edges.lower!= nullptr){
        edges.lower->render(*target);
    }
    if (edges.left!= nullptr ){
        edges.left->render(*target);
    }
    if (edges.right!= nullptr){
        edges.right->render(*target);
    }
}
void Box::deleteEdge(const std::string &posWall) {
    if (posWall=="upper"){
        edges.upper->hidden= true;
    }
    if (posWall=="lower"){
        edges.lower->hidden= true;
    }
    if (posWall=="left"){
        edges.left->hidden= true;
    }
    if (posWall=="right"){
        edges.right->hidden= true;
    }
}

void Box::addEdge(const std::shared_ptr<Wall>& wall,const std::string& posWall) {
    if (posWall=="upper"){
        edges.upper=wall;
    }
    if (posWall=="lower"){
        edges.lower=wall;
    }
    if (posWall=="left"){
        edges.left=wall;
    }
    if (posWall=="right"){
        edges.right=wall;
    }

}

Edges Box::getEdges() {
    return edges;
}

sf::Vector2f Box::getCoordinates() {
    return sprite.getPosition();
}
