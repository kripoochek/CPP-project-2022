#ifndef MY_TANKS_IN_LABIRINT_MOVEMENTCOMPONENT_H
#define MY_TANKS_IN_LABIRINT_MOVEMENTCOMPONENT_H

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <Box2D/Box2D.h>

#include <cmath>
#include <vector>
#include <deque>
#include <map>
#include <utility>
#include <memory>
#include <iostream>
#include<fstream>
#include <chrono>

struct MovementComponent {
    MovementComponent(sf::Sprite& sprite, b2Body* body, float maxVelocityMove, float currentVelocityMove, float maxVelocityRotate, float acceleration, float deceleration);

    [[nodiscard]] sf::Vector2f getVelocity() const;

    //Functions
    void move(bool isForward, float dt);
    void rotate(bool clockwise, float dt);

    void update(float dt);

    void stopVelocity();
    void stopVelocityX();
    void stopVelocityY();
private:
    const float SCALE = 30.f;
    const float DEG = 57.29577f;

    sf::Sprite &sprite;
    b2Body* body;
    float angle;
    float maxVelocityMove;
    float maxVelocityRotate;
    float currentVelocityMove;

    sf::Vector2f velocity;
    float acceleration;
    float deceleration;

    // solution, to start stop vehicle (tank)
    std::chrono::time_point<std::chrono::system_clock, std::chrono::duration<double>> lastMoveCommandTime;
    std::chrono::duration<double> intervalToStopMovement;

    // gracefully reduces velocity to zero;
    bool isStopMove();
    void gracefullyReduceVelocity(float dt);
};

#endif //MY_TANKS_IN_LABIRINT_MOVEMENTCOMPONENT_H