#include "RoundHostState.h"
#include "GameState.h"
#include "NetworkServer.h"
#include "GameStateSerializator.h"
#include <SFML/Graphics.hpp>

RoundHostState::RoundHostState(std::shared_ptr<sf::RenderWindow> window,
                       std::map<std::string, sf::Keyboard::Key> supportedKey,
                       std::shared_ptr<std::vector<std::shared_ptr<State>>> states, std::vector<Result> &scores, std::shared_ptr<NetworkServer> networkServer) : RoundState(
                           std::move(window), std::move(supportedKey), std::move(states), scores, false
                       ), networkServer(networkServer) {
    initWorld();
    initPlayers();
    initFonts();
    initFunctionsForNetworkServer();
};

void RoundHostState::updateInput(float dt) {
    if (sf::Keyboard::isKeyPressed(keybindings["START_GAME"]) && isWindowFocused) {
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
    if (isWindowFocused) {
        for (auto key : actionKeys) {
            if (sf::Keyboard::isKeyPressed(key)) {
                networkServer->pressedKeysQueue.push({ 0, key });
            }
        }
    }

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
}

void RoundHostState::update(float dt) {
    if (networkServer->isGameStarted) {
        networkServer->Update(-1, false);
        RoundState::update(dt);
        networkServer->sendAllClientsNewGameState(GameStateSerializator::serialize(shared_from_this()));
        return;
    }
    updateInput(dt);
}

void RoundHostState::initPlayers() {
    map = std::make_shared<Map>(world, sf::Vector2f(200,50),
                               textures->Box,
                               textures->VerticalBorder,
                               textures->HorizontalBorder);
    players.clear(); // because of GameState constructor
    players.push_back( std::make_shared<Player>(world, 550, 100, 5, 0, textures->FirstPlayerIdle));
    collisionManager = std::make_shared<CollisionManager>(map, players);
}

void RoundHostState::render(std::shared_ptr<sf::RenderTarget> target) {
    RoundState::render(target);

    if (!networkServer->isGameStarted) {
        sf::Text text;
        text.setFont(font);
        text.setString("Press P to start...");
        text.setFillColor(sf::Color::White);
        text.setCharacterSize(16);
        text.setPosition(sf::Vector2f{ 1090, 10 });
        target->draw(text);
    }

}

void RoundHostState::initFunctionsForNetworkServer() {
    networkServer->addPlayerFunc = [&](){
        int id = getNewPlayerId();
        auto player = std::make_shared<Player>(world, 250 + 100 * id, 100, 5, id, textures->getPlayerTextureById(id));
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

int RoundHostState::getNewPlayerId() {
    for (int i = 0; i < players.size(); i++) {
        if (players[i] == nullptr) { return i; }
    }
    return players.size();
}