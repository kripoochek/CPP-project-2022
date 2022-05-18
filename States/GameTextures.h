#ifndef MY_TANKS_IN_LABIRINT_GAMETEXTURES_H
#define MY_TANKS_IN_LABIRINT_GAMETEXTURES_H

#include <vector>
#include "Entity.h"

struct GameTextures {
public:
    // loads assets into GameTextures fields.
    GameTextures();

    // texture of bullet.
    sf::Texture Bullet;

    // textures of tanks, playable models.
    sf::Texture FirstPlayerIdle;
    sf::Texture SecondPlayerIdle;

    // labyrinth borders.
    sf::Texture VerticalBorder;
    sf::Texture HorizontalBorder;

    // labyrinth box plate.
    sf::Texture Box;

    // menu backgroundLayout.
    sf::Texture MenuBackground;

    sf::Texture& getPlayerTextureById(int id);
};

#endif //MY_TANKS_IN_LABIRINT_GAMETEXTURES_H
