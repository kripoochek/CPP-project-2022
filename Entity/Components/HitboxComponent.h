#ifndef MY_TANKS_IN_LABIRINT_HITBOXCOMPONENT_H
#define MY_TANKS_IN_LABIRINT_HITBOXCOMPONENT_H

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <Box2D/Box2D.h>

#include <vector>
#include <map>
#include <utility>
#include <memory>
#include <iostream>
#include <fstream>

struct HitboxComponent {
    HitboxComponent(sf::Sprite& sprite, float offsetX, float offsetY, float width, float height);

    //Functions
    bool intersects(const sf::FloatRect &frect);

    //Getters
    const sf::Vector2f& getPosition() const;
    sf::FloatRect getNextPosition(const sf::Vector2f& velocity);
    sf::FloatRect getGlobalBounds() const;

    //Setters
    void setPosition(const sf::Vector2f& position);
    void setPosition(float x, float y);
    void setOrigin(float x, float y);

    bool intersect(std::shared_ptr<HitboxComponent> other);

    void update();
    void render(sf::RenderTarget& target);

private:
    sf::Sprite &sprite;
    sf::RectangleShape hitbox;
    float offsetX, offsetY;
};

#endif //MY_TANKS_IN_LABIRINT_HITBOXCOMPONENT_H
