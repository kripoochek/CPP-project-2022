#include "GameClientState.h"
#include "NetworkClient.h"
#include "../Serialization/GameStateSerializator.h"
#include "../Serialization/proto/GameState.pb.h"
#include "../Entity/Map/Box.h"


#include <ctime>
#include <chrono>
#include <iomanip>

GameClientState::GameClientState(std::shared_ptr<sf::RenderWindow> window,
                     std::map<std::string, sf::Keyboard::Key> supportedKey,
                     std::shared_ptr<std::vector<std::shared_ptr<State>>> states) :
        State(std::move(window), std::move(supportedKey), std::move(states)){
    initKeybindings();
    initTextures();
    initConnection();
}

void GameClientState::initKeybindings() {
    std::ifstream file("../Config/gamestate_keybinds.ini");

    if (file.is_open()){
        std::string action;
        std::string keyBinding;
        while(file >> action >> keyBinding){
            keybindings[action] = supportedKeys[keyBinding];
        }
    }
}

void GameClientState::initTextures() {
    textures = std::make_shared<GameTextures>();
}

void GameClientState::initConnection() {
    networkClient.Connect("127.0.0.1", 60000);
}

void GameClientState::update(float dt) {
    updateInput(dt);
    if (networkClient.IsConnected()) {
        while (!networkClient.Incoming().empty()) {
            auto msg = networkClient.Incoming().pop_front().msg;

            if (msg.header.id == GameMessage::NEW_GAME_STATE) {
                char str[25000];
                msg >> str;
                serialized::GameState gs;
                gs.ParseFromArray(str, 10000);
                std::cout << "New game state: " << gs.map().rowsnumber() << "\n";

                // TODO: update map only when new map, not on every message
                map = std::make_shared<Map>(
                                gs.map().rowsnumber(), 
                                gs.map().columnsnumber(),
                                sf::Vector2f(200,50),
                               textures->Box,
                               textures->VerticalBorder,
                               textures->HorizontalBorder);
                players.clear();

                GameStateSerializator::deserializeMap(gs, map, textures->VerticalBorder, textures->HorizontalBorder);
                GameStateSerializator::deserializePlayers(gs, players, textures);
            }
            if (msg.header.id == GameMessage::SERVER_STOP) {
                networkClient.Disconnect();
            }
        }
    } else {
        // TODO: remove player

        // quit = true;
    }
}

void GameClientState::render(std::shared_ptr<sf::RenderTarget> target) {
    if (!target){ target = window; }
    if(map.get() != nullptr) {
        map->render(target);
    }

    for (const std::shared_ptr<Player>&  player: players) {
        player->render(*target);
    }
}

void GameClientState::updateInput(float dt) {
    if (sf::Keyboard::isKeyPressed(keybindings["CLOSE"]) && isWindowFocused){
        // TODO: put it in NetworkClient and call in destructor
        olc::net::message<GameMessage> newGameStateMsg;
        newGameStateMsg.header.id = GameMessage::CLIENT_DISCONNECT;   
        newGameStateMsg << 1;
        networkClient.Send(newGameStateMsg);

        // networkClient.Disconnect();
    }
}