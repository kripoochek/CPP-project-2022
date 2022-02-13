#ifndef SIMPLE_THEME_H_
#define SIMPLE_THEME_H_

#include "theme.h"

struct SimpleTheme : Theme {
    void applyBox(sf::RectangleShape &box);
    void applyWall(sf::RectangleShape &wall);
};
#endif