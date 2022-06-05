#include "RoundClientState.h"
#include "NetworkClient.h"
#include "NetworkServer.h"
#include "../Serialization/GameStateSerializator.h"
#include "../Serialization/proto/GameState.pb.h"
#include "../Entity/Map/Box.h"
#include "MainMenuState.h"


#include <ctime>
#include <chrono>
#include <thread>
#include <iomanip>

RoundClientState::RoundClientState(std::shared_ptr<sf::RenderWindow> window,
                     std::map<std::string, sf::Keyboard::Key> supportedKey,
                     std::shared_ptr<std::vector<std::shared_ptr<State>>> states,
                     std::vector<Result> &scores, std::shared_ptr<NetworkClient> networkClient) :
        RoundState(std::move(window), std::move(supportedKey), std::move(states), scores, false), networkClient(networkClient){
    // because of GameState constructor
    map = nullptr;
    players.clear();
}

void RoundClientState::update(float dt) {
    updateInput(dt);
    if (networkClient->IsConnected()) {
        while (!networkClient->Incoming().empty()) {
            auto msg = networkClient->Incoming().pop_front().msg;

            if (msg.header.id == GameMessage::NEW_GAME_STATE) {
                char str[NEW_STATE_MESSAGE_SIZE];
                int bulletsNumber;
                msg >> str >> bulletsNumber;
                serialized::GameState gs;
                gs.ParseFromArray(str, NEW_STATE_MESSAGE_SIZE);
                players.clear();
                bullets.clear();

                GameStateSerializator::deserializePlayers(world, gs, players, textures);
                GameStateSerializator::deserializeBullets(world, gs, bullets, textures->Bullet, bulletsNumber);
            }
            if (msg.header.id == GameMessage::NEW_GAME_MAP) {
                char str[5000];
                msg >> str;
                serialized::Map gs;
                gs.ParseFromArray(str, 5000);
                map = std::make_shared<Map>(
                            world,
                            gs.rowsnumber(), 
                            gs.columnsnumber(),
                            sf::Vector2f(200,50),
                            textures->Box,
                            textures->VerticalBorder,
                            textures->HorizontalBorder);
                GameStateSerializator::deserializeMap(world, gs, map, textures->VerticalBorder, textures->HorizontalBorder);
            }
            if (msg.header.id == GameMessage::CLIENT_CONNECTED) {
                int id;
                msg >> id;
                networkClient->setId(id);
            }
            if (msg.header.id == GameMessage::SERVER_STOP) {
                networkClient->Disconnect();
            }
        }
    } else {
        networkClient->sendDisconnectMessage();
        // Time for networkClient->Send to deliver message
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        states->push_back(std::make_shared<MainMenuState>(window, supportedKeys, states));
    }
}

void RoundClientState::updateInput(float dt) {
    if (!isWindowFocused) { return; }
    if (sf::Keyboard::isKeyPressed(keybindings["CLOSE"])){
        networkClient->sendDisconnectMessage();
        // Time for networkClient->Send to deliver message
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        // states->push_back(std::make_shared<MainMenuState>(window, supportedKeys, states));
    }
    const std::vector<sf::Keyboard::Key> actionKeys{
        keybindings["MOVE_UP2"], 
        keybindings["MOVE_DOWN2"],
        keybindings["MOVE_LEFT2"],
        keybindings["MOVE_RIGHT2"],
        keybindings["ATTACK2"]
    };
    for (auto key : actionKeys) {
        if (sf::Keyboard::isKeyPressed(key)) {
            networkClient->sendOnKeyPressedMessage(key);
        }
    }
}