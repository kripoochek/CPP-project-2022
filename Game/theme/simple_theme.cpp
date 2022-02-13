#include "SFML/Graphics.hpp"
#include "simple_theme.h"
#include "utils.h"
#include <iostream>

void SimpleTheme::applyBox(sf::RectangleShape &box) {
    std::vector<sf::Color> colors = { sf::Color{0xCCCC99FF}, sf::Color{0xCCCCCCFF} };
    box.setFillColor(colors[randNum(0, colors.size() - 1)]);
}

void SimpleTheme::applyWall(sf::RectangleShape &wall) {
    wall.setFillColor(sf::Color{0x666666FF});
}