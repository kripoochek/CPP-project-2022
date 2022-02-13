#include "GameMap.h"
GameMap::GameMap(sf::RenderWindow* window) {
    Theme* theme = new SimpleTheme();
    mapTex.create(window->getSize().x, window->getSize().y);
    map.setTheme(theme);
    map.generate();
    map.draw(mapTex);
    gameMapView=sf::Sprite(mapTex.getTexture());
}

sf::Sprite GameMap::getSprite() {
    return gameMapView;
}