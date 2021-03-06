#include "GameState.h"
#include "RoundState.h"
#include "RoundHostState.h"
#include "RoundClientState.h"
#include "NetworkServer.h"
#include "NetworkClient.h"
#include <iostream>

GameState::GameState(std::shared_ptr<sf::RenderWindow> window,
                     std::map<std::string, sf::Keyboard::Key> supportedKey,
                     std::shared_ptr<std::vector<std::shared_ptr<State>>> states, int numOfRounds, const sf::Font &font, GameStateType type) :
        State(std::move(window), std::move(supportedKey), std::move(states)), numOfRounds(numOfRounds), font(font), type(type){
    if (type == GameStateType::HOST) {
        networkServer = std::make_shared<NetworkServer>(60000);
        networkServer->Start();
    }
    if (type == GameStateType::CLIENT) {
        std::string ip;
        std::cin >> ip;
        networkClient = std::make_shared<NetworkClient>();
        networkClient->Connect(ip, 60000);
    }
    for (int i = 0; i < MAXN; ++i){
        scores.push_back(Result(10.f, 5.f + 50.f * i, font, "P" + std::to_string(i + 1) + ":", 24, sf::Color::White));
    }
    timer = 0;
}

void GameState::render(std::shared_ptr<sf::RenderTarget> target) {

}

void GameState::updateInput(float dt) {

}

void GameState::update(float dt) {
    timer++;
    if (timer > numOfRounds){
        quit = true;
    }
    else{
        switch (type) {
            case GameStateType::LOCAL:
                {
                    states->push_back(std::make_shared<RoundState>(window, supportedKeys, states, scores, true));
                    break;
                }
            case GameStateType::CLIENT:
                {
                    states->push_back(std::make_shared<RoundClientState>(window, supportedKeys, states, scores, networkClient));
                    break;
                }
            case GameStateType::HOST:
                {
                    states->push_back(std::make_shared<RoundHostState>(window, supportedKeys, states, scores, networkServer));
                    break;
                }
        }
    }
}

void GameState::initKeybindings() {

}
