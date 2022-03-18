#ifndef THEME_H_
#define THEME_H_

#include <SFML/Graphics.hpp>

struct Theme {
    virtual void applyBox(sf::RectangleShape &box) = 0;
    virtual void applyWall(sf::RectangleShape &wall) = 0;
};
#endif