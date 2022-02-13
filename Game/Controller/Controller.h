#ifndef TANKS_IN_LABIRINT_CONTROLLER_H
#define TANKS_IN_LABIRINT_CONTROLLER_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "Tank.h"
#include "map.h"
#include "theme.h"
#include "simple_theme.h"

struct Controller {
    ///Constructors / Destructors
    Controller();
    ~Controller();

    void render();
    void running();

private:
    ///Varibles
    ///Window
    sf::RenderWindow* window = nullptr;
    sf::Event event;
    Map gameMap;
    sf::RenderTexture mapTex;
    Theme* theme;
    sf::Sprite gameMapView;
    ///Event

    ///Controller objects
    std::vector<DynamicObject*> objects;

    ///Private Functions
    void initWindow();
};

#endif //TANKS_IN_LABIRINT_CONTROLLER_H
