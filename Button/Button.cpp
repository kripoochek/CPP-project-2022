#include "Button.h"

Button::Button(float x, float y, float width, float height, const sf::Font& font, const std::string& text,
               sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor) : font(font),
               idleColor(idleColor), hoverColor(hoverColor), activeColor(activeColor) {
    shape.setPosition(sf::Vector2f(x, y));
    shape.setSize(sf::Vector2f(width, height));

    buttonState = ButtonStates::IDLE;

    this->text.setFont(font);
    this->text.setString(text);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(12);
    this->text.setPosition(shape.getPosition().x + (shape.getGlobalBounds().width / 2.f - this->text.getGlobalBounds().width / 2.f),
                           shape.getPosition().y + (shape.getGlobalBounds().height / 2.f - this->text.getGlobalBounds().height / 2.f));

    this->shape.setFillColor(this->idleColor);
}

bool Button::isPressed() const {
   return (buttonState == ButtonStates::ACTIVE);
}

void Button::update(sf::Vector2f mousePos) {
    buttonState = ButtonStates::IDLE;

    if (shape.getGlobalBounds().contains(mousePos)){
        buttonState = ButtonStates::HOVER;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            buttonState = ButtonStates::ACTIVE;
        }
    }

    switch (buttonState) {
        default:
            shape.setFillColor(sf::Color::Green);
            break;
        case ButtonStates::IDLE:
            shape.setFillColor(idleColor);
            break;
        case ButtonStates::HOVER:
            shape.setFillColor(hoverColor);
            break;
        case ButtonStates::ACTIVE:
            shape.setFillColor(activeColor);
            break;
    }
}

void Button::render(std::shared_ptr<sf::RenderTarget> target) {
    target->draw(shape);
    target->draw(text);
}




