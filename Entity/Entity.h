#ifndef MY_TANKS_IN_LABIRINT_ENTITY_H
#define MY_TANKS_IN_LABIRINT_ENTITY_H

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <vector>
#include <map>
#include <utility>
#include <memory>
#include <iostream>
#include <fstream>

#include "MovementComponent.h"

struct Entity {
    //Constructors/Destructors
    Entity();


    //Component functions
    void setTexture(sf::Texture &texture);
    void createMovementComponent(float maxVelocityMove, float maxVelocityRotate, float acceleration, float deceleration);

    //Functions
    virtual void setPosition(float x, float y);
    virtual void move(bool forward, float dt);
    virtual void rotate(bool clockwise, float dt);
    virtual void update(float dt);
    virtual void render(const std::shared_ptr<sf::RenderTarget>& target);

protected:
    sf::Sprite sprite;

    std::shared_ptr<MovementComponent> movementComponent;
private:
    void initVariables();
};


#endif //MY_TANKS_IN_LABIRINT_ENTITY_H
