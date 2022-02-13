#ifndef GAME_GAMEMAP_H
#define GAME_GAMEMAP_H
#include "map.h"
#include "simple_theme.h"
class GameMap {
private:
    Map map;
    sf::RenderTexture mapTex;
    Theme* theme;
    sf::Sprite gameMapView;
public:
    GameMap(sf::RenderWindow* window);
    sf::Sprite getSprite();
};


#endif //GAME_GAMEMAP_H
