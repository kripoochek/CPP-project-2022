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

#include <chrono>

struct MovementComponent {
    MovementComponent(sf::Sprite& sprite, float maxVelocityMove, float maxVelocityRotate, float acceleration, float deceleration);


    [[nodiscard]] sf::Vector2f getVelocity() const;


    //Functions
    void move(bool isForward, float dt);
    void rotate(bool clockwise, float dt);
    void update(float dt);
    void stop();
private:
    sf::Sprite &sprite;

    float maxVelocityMove;
    float maxVelocityRotate;

    float currentVelocityMove;

    // solution, to start stop vehicle (tank)
    std::chrono::time_point<std::chrono::system_clock, std::chrono::duration<double>> lastMoveCommandTime;
    std::chrono::duration<double> intervalToStopMovement;

    sf::Vector2f velocity;
    float acceleration;
    float deceleration;

    // assert if there's no movements actions last time;
    bool isStopMove();

    // gracefully reduces velocity to zero;
    void gracefullyReduceVelocity(float dt);
};

#endif //MY_TANKS_IN_LABIRINT_MOVEMENTCOMPONENT_H