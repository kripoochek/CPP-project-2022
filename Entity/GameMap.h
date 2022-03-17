#ifndef MY_TANKS_IN_LABIRINT_GAMEMAP_H
#define MY_TANKS_IN_LABIRINT_GAMEMAP_H


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


#endif //MY_TANKS_IN_LABIRINT_GAMEMAP_H
