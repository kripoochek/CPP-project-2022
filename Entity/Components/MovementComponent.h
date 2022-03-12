#ifndef MY_TANKS_IN_LABIRINT_MOVEMENTCOMPONENT_H
#define MY_TANKS_IN_LABIRINT_MOVEMENTCOMPONENT_H

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include <cmath>
#include <vector>
#include <map>
#include <utility>
#include <memory>
#include <iostream>
#include<fstream>

struct MovementComponent {
    MovementComponent(sf::Sprite& sprite, float maxVelocity);


    [[nodiscard]] sf::Vector2f getVelocity() const;


    //Functions
    void move(float dir_x, float dir_y, float dt);
    void rotate(bool turnDir);
    void update(float dt);
private:
    sf::Sprite &sprite;

    float maxVelocity;

    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    sf::Vector2f deceleration;

    //Initializer functions

};

#endif //MY_TANKS_IN_LABIRINT_MOVEMENTCOMPONENT_H
