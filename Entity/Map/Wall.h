
#ifndef MY_TANKS_IN_LABIRINT_WALL_H
#define MY_TANKS_IN_LABIRINT_WALL_H



#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


class Wall {
private:
    sf::Sprite wall;
    sf::Vector2f coordinates;
public:
    Wall(sf::Vector2f coordinates_);
    void initSize(bool position);
};


#endif //MY_TANKS_IN_LABIRINT_WALL_H
