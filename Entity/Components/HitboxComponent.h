#ifndef MY_TANKS_IN_LABIRINT_HITBOXCOMPONENT_H
#define MY_TANKS_IN_LABIRINT_HITBOXCOMPONENT_H

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

struct HitboxComponent {
    HitboxComponent(sf::Sprite& sprite, float offsetX, float offsetY, float width, float height);

    //Functions
    bool checkIntersect(const sf::FloatRect &frect);

    //Getters
    sf::FloatRect getGlobalBounds() const;
    bool intersect(std::shared_ptr<HitboxComponent> other);
    void update();
    void render(sf::RenderTarget& target);
private:
    sf::Sprite &sprite;
    sf::RectangleShape hitboxShape;
    float offsetX, offsetY;
};

#endif //MY_TANKS_IN_LABIRINT_HITBOXCOMPONENT_H
