#include "GameHostState.h"
#include "GameState.h"
#include "NetworkServer.h"
#include "GameStateSerializator.h"

GameHostState::GameHostState(std::shared_ptr<sf::RenderWindow> window,
                       std::map<std::string, sf::Keyboard::Key> supportedKey,
                       std::shared_ptr<std::vector<std::shared_ptr<State>>> states) : GameState(
                           std::move(window), std::move(supportedKey), std::move(states)
                       ), networkServer(std::make_shared<NetworkServer>(60000)) {

    networkServer->Start();
};

void GameHostState::update(float dt) {
    if (networkServer->serializedGameState.map().rowsnumber() == 0) {
        networkServer->serializedGameState = GameStateSerializator::serialize(shared_from_this());
    }
    GameState::update(dt);
}