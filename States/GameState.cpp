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
    if (sf::Keyboard::isKeyPressed(keybinds["MOVE_LEFT"])){
        player->move(dt, -1, 0);
    }
    if (sf::Keyboard::isKeyPressed(keybinds["MOVE_RIGHT"])){
        player->move(dt, 1, 0);
    }
    if (sf::Keyboard::isKeyPressed(keybinds["MOVE_UP"])){
        player->move(dt, 0, -1);
    }
    if (sf::Keyboard::isKeyPressed(keybinds["MOVE_DOWN"])){
        player->move(dt, 0, 1);
    }

    if (sf::Keyboard::isKeyPressed(keybinds["CLOSE"])){
        quit = true;
    }
}

void GameState::update(float dt) {
    updateMousePositions();
    updateInput(dt);
    player->update(dt);
}

void GameState::render(std::shared_ptr<sf::RenderTarget> target) {
    if (!target){ target = window;}
    player->render(target);
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
    std::shared_ptr<sf::Texture> temp = std::make_shared<sf::Texture>();
    if (!textures["PLAYER_IDLE"].loadFromFile("../Resources/Images/Sprites/Player/tank1.png")){
        throw std::exception();
    }
}

void GameState::initPlayers() {
    player = std::make_shared<Player>(0, 0, textures["PLAYER_IDLE"]);
}


