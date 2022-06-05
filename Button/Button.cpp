#include "Button.h"

Button::Button(float x, float y, float width, float height,
               const sf::Font& font, const std::string& text, int characterSize,
               sf::Color textIdleColor, sf::Color textHoverColor, sf::Color textActiveColor,
               sf::Color idleColor, sf::Color hoverColor, sf::Color activeColor) :
               idleColor(idleColor), hoverColor(hoverColor), activeColor(activeColor),
               textIdleColor(textIdleColor), textHoverColor(textHoverColor), textActiveColor(textActiveColor) {
    shape.setOrigin(width / 2, height / 2);
    shape.setPosition(sf::Vector2f(x, y));
    shape.setSize(sf::Vector2f(width, height));
    this->shape.setFillColor(idleColor);

    buttonState = ButtonStates::IDLE;

    this->text.setOrigin(width / 2, height / 2);
    this->text.setFont(font);
    this->text.setString(text);
    this->text.setFillColor(sf::Color::White);
    this->text.setCharacterSize(characterSize);
    this->text.setPosition(shape.getPosition().x + (shape.getGlobalBounds().width / 2.f - this->text.getGlobalBounds().width / 2.f),
                           shape.getPosition().y + (shape.getGlobalBounds().height / 2.f - this->text.getGlobalBounds().height / 2.f));
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
            shape.setFillColor(sf::Color::Red);
            text.setFillColor(sf::Color::Red);
            break;
        case ButtonStates::IDLE:
            shape.setFillColor(idleColor);
            text.setFillColor(textIdleColor);
            break;
        case ButtonStates::HOVER:
            shape.setFillColor(hoverColor);
            text.setFillColor(textHoverColor);
            break;
        case ButtonStates::ACTIVE:
            shape.setFillColor(activeColor);
            text.setFillColor(textActiveColor);
            break;
    }
}

void Button::render(sf::RenderTarget &target) {
    target.draw(shape);
    target.draw(text);
}




