#include "State.h"

#include <utility>

State::State(std::shared_ptr<sf::RenderWindow> window,
             std::map<std::string, sf::Keyboard::Key> supportedKeys,
             std::shared_ptr<std::vector<std::shared_ptr<State>>> states) :
             window(std::move(window)), quit(false),
             supportedKeys(std::move(supportedKeys)),
             states(std::move(states)){

}

void State::updateMousePositions() {
    mousePosScreen = sf::Mouse::getPosition();
    mousePosWindow = sf::Mouse::getPosition(*window);
    mousePosView = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
}



bool State::getQuit() const { return quit; }

void State::endState() { quit = true; }


