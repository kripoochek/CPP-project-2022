#include "GameHostState.h"
#include "GameState.h"
#include "NetworkServer.h"

GameHostState::GameHostState(std::shared_ptr<sf::RenderWindow> window,
                       std::map<std::string, sf::Keyboard::Key> supportedKey,
                       std::shared_ptr<std::vector<std::shared_ptr<State>>> states) : GameState(
                           std::move(window), std::move(supportedKey), std::move(states)
                       ), networkServer{60000, std::make_shared<GameHostState>(this)} {
    networkServer.Start();
};