
#ifndef MY_TANKS_IN_LABIRINT_WALL_H
#define MY_TANKS_IN_LABIRINT_WALL_H


#include "HitboxComponent.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
class Wall {
private:
    sf::Sprite sprite;
public:
    std::shared_ptr<HitboxComponent> hitboxComponent;
    bool hidden=false;
    Wall(sf::Vector2f coordinates,const sf::Texture& texture_);
    void setTexture(const sf::Texture& texture_);
    void setPosition(sf::Vector2f coordinates);
    void render(sf::RenderTarget& target);
    //void createMovementComponent(float maxVelocityMove, float maxVelocityRotate, float acceleration, float deceleration);
    void initComponents();

    void createHitboxComponent(sf::Sprite &sprite, float offsetX, float offsetY, float width, float height);
};


#endif //MY_TANKS_IN_LABIRINT_WALL_H
