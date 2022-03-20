#include "GameState.h"

GameState::GameState(std::shared_ptr<sf::RenderWindow> window,
                     std::map<std::string, sf::Keyboard::Key> supportedKey,
                     std::shared_ptr<std::vector<std::shared_ptr<State>>> states) :
        State(std::move(window), std::move(supportedKey), std::move(states)){
    initKeybindings();
    initTextures();
    initPlayers();
}

void GameState::updateInput(float dt) {
    //Update player input
    if (sf::Keyboard::isKeyPressed(keybindings["MOVE_LEFT1"])){
        players[0]->rotate(false, dt);
    }
    if (sf::Keyboard::isKeyPressed(keybindings["MOVE_RIGHT1"])){
        players[0]->rotate(true, dt);
    }
    if (sf::Keyboard::isKeyPressed(keybindings["MOVE_UP1"])){
        players[0]->move(true, dt);
    }
    if (sf::Keyboard::isKeyPressed(keybindings["MOVE_DOWN1"])){
        players[0]->move(false, dt);
    }

    if (sf::Keyboard::isKeyPressed(keybindings["CLOSE"])){
        quit = true;
    }
    if (sf::Keyboard::isKeyPressed(keybindings["MOVE_LEFT2"])){
        players[1]->rotate(false, dt);
    }
    if (sf::Keyboard::isKeyPressed(keybindings["MOVE_RIGHT2"])){
        players[1]->rotate(true, dt);
    }
    if (sf::Keyboard::isKeyPressed(keybindings["MOVE_UP2"])){
        players[1]->move(true, dt);
    }
    if (sf::Keyboard::isKeyPressed(keybindings["MOVE_DOWN2"])){
        players[1]->move(false, dt);
    }
}

void GameState::update(float dt) {
    updateMousePositions();
    updateInput(dt);
    for (const std::shared_ptr<Player>& player:players) {
        player->update(dt);
    }
}

void GameState::render(std::shared_ptr<sf::RenderTarget> target) {
    if (!target){ target = window;}
    map->render(target);
    for (const std::shared_ptr<Player>&  player:players) {
        player->render(target);
    }
}

void GameState::initKeybindings() {
    std::ifstream file("../Config/gamestate_keybinds.ini");

    if (file.is_open()){
        std::string action;
        std::string keyBinding;
        while(file >> action >> keyBinding){
            keybindings[action] = supportedKeys[keyBinding];
        }
    }
}

void GameState::initPlayers() {
    map= std::make_shared<Map>(sf::Vector2f(200,50),
                               textures->Box,
                               textures->VerticalBorder,
                               textures->HorizontalBorder);
    players.push_back( std::make_shared<Player>(50, 50, textures->FirstPlayerIdle));
    players.push_back( std::make_shared<Player>(50, 50, textures->SecondPlayerIdle));
}


void GameState::initTextures() {
    textures = std::make_shared<GameTextures>();
}



