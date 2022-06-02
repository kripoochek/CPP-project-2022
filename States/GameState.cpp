#include "GameState.h"

GameState::GameState(std::shared_ptr<sf::RenderWindow> window,
                     std::map<std::string, sf::Keyboard::Key> supportedKey,
                     std::shared_ptr<std::vector<std::shared_ptr<State>>> states, int numOfRounds, const sf::Font &font) :
        State(std::move(window), std::move(supportedKey), std::move(states)), numOfRounds(numOfRounds), font(font){
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
        states->push_back(std::make_shared<RoundState>(window, supportedKeys, states, scores));
    }
}

void GameState::initKeybindings() {

}
