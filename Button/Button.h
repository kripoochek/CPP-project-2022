#ifndef MY_TANKS_IN_LABIRINT_BUTTON_H
#define MY_TANKS_IN_LABIRINT_BUTTON_H

#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>


#include <iostream>
#include <memory>
#include <utility>

enum class ButtonStates{ IDLE, HOVER, ACTIVE};

struct Button {
    Button(float x, float y, float width, float height,
           const sf::Font& font, const std::string& text,
           sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor);
    //Functions
    bool isPressed() const;

    void update(sf::Vector2f mousePos);
    void render(std::shared_ptr<sf::RenderTarget> target);
private:
    sf::RectangleShape shape;
    sf::Font font;
    sf::Text text;

    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;

    ButtonStates buttonState;

};

#endif //MY_TANKS_IN_LABIRINT_BUTTON_H
