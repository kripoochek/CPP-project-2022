
#ifndef MY_TANKS_IN_LABIRINT_WALL_H
#define MY_TANKS_IN_LABIRINT_WALL_H



#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>

class Wall {
private:
    sf::Sprite wall;
    sf::Vector2f coordinates;
public:
    Wall(sf::Vector2f coordinates_,const sf::Texture& texture_,bool position);
    void initSize(bool position);
    void setTexture(const sf::Texture& texture_);
    void setPosition(sf::Vector2f coordinates);
};


#endif //MY_TANKS_IN_LABIRINT_WALL_H
