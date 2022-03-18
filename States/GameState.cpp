#include "GameState.h"

GameState::GameState(std::shared_ptr<sf::RenderWindow> window,
                     std::map<std::string, sf::Keyboard::Key> supportedKey,
                     std::shared_ptr<std::vector<std::shared_ptr<State>>> states) :
        State(std::move(window), std::move(supportedKey), std::move(states)){
    initKeybinds();
    initTextures();
    initPlayers();
}

void GameState::updateInput(float dt) {
    //Update player input
    if (sf::Keyboard::isKeyPressed(keybinds["MOVE_LEFT1"])){
        players[0]->rotate(false, dt);
    }
    if (sf::Keyboard::isKeyPressed(keybinds["MOVE_RIGHT1"])){
        players[0]->rotate(true, dt);
    }
    if (sf::Keyboard::isKeyPressed(keybinds["MOVE_UP1"])){
        players[0]->move(true, dt);
    }
    if (sf::Keyboard::isKeyPressed(keybinds["MOVE_DOWN1"])){
        players[0]->move(false, dt);
    }

    if (sf::Keyboard::isKeyPressed(keybinds["CLOSE"])){
        quit = true;
    }
    if (sf::Keyboard::isKeyPressed(keybinds["MOVE_LEFT2"])){
        players[1]->rotate(false, dt);
    }
    if (sf::Keyboard::isKeyPressed(keybinds["MOVE_RIGHT2"])){
        players[1]->rotate(true, dt);
    }
    if (sf::Keyboard::isKeyPressed(keybinds["MOVE_UP2"])){
        players[1]->move(true, dt);
    }
    if (sf::Keyboard::isKeyPressed(keybinds["MOVE_DOWN2"])){
        players[1]->move(false, dt);
    }
}

void GameState::update(float dt) {
    updateMousePositions();
    updateInput(dt);
    for (auto player:players) {
        player->update(dt);
    }
}

void GameState::render(std::shared_ptr<sf::RenderTarget> target) {
    if (!target){ target = window;}
    box->render(target);
    for (auto player:players) {
        player->render(target);
    }
}

void GameState::initKeybinds() {
    std::ifstream file("../Config/gamestate_keybinds.ini");

    if (file.is_open()){
        std::string key;
        std::string key2;
        while(file >> key >> key2){
            keybinds[key] = supportedKeys[key2];
        }
    }
}

void GameState::initTextures() {
    if (!textures["PLAYER_IDLE1"].loadFromFile("../Resources/Images/Sprites/Player/tank1.png")){
        throw std::exception();
    }
    if (!textures["PLAYER_IDLE2"].loadFromFile("../Resources/Images/Sprites/Player/tank0.png")){
        throw std::exception();
    }
    if (!textures["VERTICAL_BORDER"].loadFromFile("../Resources/Images/Sprites/vertical.png")){
        throw std::exception();
    }
    if (!textures["HORIZONTAL_BORDER"].loadFromFile("../Resources/Images/Sprites/horizontal.png")){
        throw std::exception();
    }
    if (!textures["BOX"].loadFromFile("../Resources/Images/Backgrounds/grass.png")){
        throw std::exception();
    }
}

void GameState::initPlayers() {
    box= std::make_shared<Box>(sf::Vector2f(0,0),textures["BOX"],textures["VERTICAL_BORDER"],textures["HORIZONTAL_BORDER"]);
    players.push_back( std::make_shared<Player>(0, 0, textures["PLAYER_IDLE1"]));
    players.push_back( std::make_shared<Player>(0, 0, textures["PLAYER_IDLE2"]));
    /*for (auto player:players){
        player = std::make_shared<Player>(0, 0, textures["PLAYER_IDLE"]);
    }*/
}



