#include "GameHostState.h"
#include "GameState.h"
#include "NetworkServer.h"
#include "GameStateSerializator.h"
#include <SFML/Graphics.hpp>

GameHostState::GameHostState(std::shared_ptr<sf::RenderWindow> window,
                       std::map<std::string, sf::Keyboard::Key> supportedKey,
                       std::shared_ptr<std::vector<std::shared_ptr<State>>> states) : GameState(
                           std::move(window), std::move(supportedKey), std::move(states)
                       ), networkServer(std::make_shared<NetworkServer>(60000)) {
    initPlayers();
    initFonts();
    initFunctionsForNetworkServer();
    networkServer->Start();
};

void GameHostState::updateInput(float dt) {
    if (!isWindowFocused) { return; }
    if (sf::Keyboard::isKeyPressed(keybindings["CLOSE"])){
        quit = true;
    }
    if (sf::Keyboard::isKeyPressed(keybindings["START_GAME"])) {
        networkServer->startGame();
    }

    if (!networkServer->isGameStarted) { return; }

    const std::vector<sf::Keyboard::Key> actionKeys{
        keybindings["MOVE_UP2"], 
        keybindings["MOVE_DOWN2"],
        keybindings["MOVE_LEFT2"],
        keybindings["MOVE_RIGHT2"],
        keybindings["ATTACK2"]
    };
    for (auto key : actionKeys) {
        if (sf::Keyboard::isKeyPressed(key)) {
            networkServer->pressedKeysQueue.push({ 0, key });
        }
    }
}

void GameHostState::update(float dt) {
    GameState::update(dt);
    networkServer->Update(-1, false);
    while (!networkServer->pressedKeysQueue.empty()) {
        auto& [id, key] = networkServer->pressedKeysQueue.back();
        networkServer->pressedKeysQueue.pop();
        if (key == keybindings["ATTACK2"]){
            players[id]->attack(bullets, textures->Bullet, dt);
        }
        if (key == keybindings["MOVE_LEFT2"]){
            players[id]->rotate(false, dt);
        }
        if (key == keybindings["MOVE_RIGHT2"]){
            players[id]->rotate(true, dt);
        }
        if (key == keybindings["MOVE_UP2"]){
            players[id]->move(true, dt);
        }
        if (key == keybindings["MOVE_DOWN2"]){
            players[id]->move(false, dt);
        }
    }
    networkServer->sendAllClientsNewGameState(GameStateSerializator::serialize(shared_from_this()));
}

void GameHostState::initPlayers() {
    map = std::make_shared<Map>(sf::Vector2f(200,50),
                               textures->Box,
                               textures->VerticalBorder,
                               textures->HorizontalBorder);
    players.clear(); // because of GameState constructor
    players.push_back( std::make_shared<Player>(250, 100, 5, 0, textures->FirstPlayerIdle));
    collisionManager = std::make_shared<CollisionManager>(map, players);
}

void GameHostState::render(std::shared_ptr<sf::RenderTarget> target) {
    GameState::render(target);

    if (!networkServer->isGameStarted) {
        sf::Text text;
        text.setFont(font);
        text.setString("Press P to start...");
        text.setFillColor(sf::Color::White);
        text.setCharacterSize(16);
        text.setPosition(sf::Vector2f{ 10, 10 });
        target->draw(text);
    }

}

void GameHostState::initFunctionsForNetworkServer() {
    networkServer->addPlayerFunc = [&](){
        int id = getNewPlayerId();
        auto player = std::make_shared<Player>(250 + 100 * id, 100, 5, id, textures->getPlayerTextureById(id));
        if (id == players.size()) { players.push_back(player); }
        else { players[id] = player; }  
        return std::make_pair(id, GameStateSerializator::serialize(shared_from_this()));
    };
    networkServer->deletePlayerFunc = [&](int id) {
        players[id] = nullptr;
        return GameStateSerializator::serialize(shared_from_this());
    };
    networkServer->getPlayersNumberFunc = [&]() {
        return players.size();
    };
}

int GameHostState::getNewPlayerId() {
    for (int i = 0; i < players.size(); i++) {
        if (players[i] == nullptr) { return i; }
    }
    return players.size();
}