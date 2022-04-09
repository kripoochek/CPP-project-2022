#ifndef MY_TANKS_IN_LABIRINT_WALL_H
#define MY_TANKS_IN_LABIRINT_WALL_H

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>

#include "Entity.h"

struct Wall : Entity {
    Wall(float x, float y, sf::Texture& texture);

    void setHidden(bool type);
    bool isHidden() const;

    void render(sf::RenderTarget& target) final;
private:
    bool hidden;
};

#endif //MY_TANKS_IN_LABIRINT_WALL_H
