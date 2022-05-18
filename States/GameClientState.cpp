#include "GameClientState.h"
#include "NetworkClient.h"
#include "NetworkServer.h"
#include "../Serialization/GameStateSerializator.h"
#include "../Serialization/proto/GameState.pb.h"
#include "../Entity/Map/Box.h"


#include <ctime>
#include <chrono>
#include <thread>
#include <iomanip>

GameClientState::GameClientState(std::shared_ptr<sf::RenderWindow> window,
                     std::map<std::string, sf::Keyboard::Key> supportedKey,
                     std::shared_ptr<std::vector<std::shared_ptr<State>>> states) :
        GameState(std::move(window), std::move(supportedKey), std::move(states)){
    initConnection();
    // because of GameState constructor
    map = nullptr;
    players.clear();
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
                char str[NEW_STATE_MESSAGE_SIZE];
                int bulletsNumber;
                msg >> str >> bulletsNumber;
                serialized::GameState gs;
                gs.ParseFromArray(str, NEW_STATE_MESSAGE_SIZE);
                for (auto i = 0; i < gs.bullets_size(); i++) {
                    std::cout << "(" << gs.bullets().at(i).x() << ", " << gs.bullets().at(i).y() << "), ";
                }
                std::cout << '\n';
                // TODO: update map only when new map, not on every message
                map = std::make_shared<Map>(
                                gs.map().rowsnumber(), 
                                gs.map().columnsnumber(),
                                sf::Vector2f(200,50),
                               textures->Box,
                               textures->VerticalBorder,
                               textures->HorizontalBorder);
                players.clear();
                bullets.clear();

                GameStateSerializator::deserializeMap(gs, map, textures->VerticalBorder, textures->HorizontalBorder);
                GameStateSerializator::deserializePlayers(gs, players, textures);
                GameStateSerializator::deserializeBullets(gs, bullets, textures->Bullet, bulletsNumber);
            }
            if (msg.header.id == GameMessage::CLIENT_CONNECTED) {
                int id;
                msg >> id;
                networkClient.setId(id);
            }
            if (msg.header.id == GameMessage::SERVER_STOP) {
                networkClient.Disconnect();
            }
        }
    } else {
        networkClient.sendDisconnectMessage();
        // Time for networkClient.Send to deliver message
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        quit = true;
    }
}

void GameClientState::updateInput(float dt) {
    if (!isWindowFocused) { return; }
    if (sf::Keyboard::isKeyPressed(keybindings["CLOSE"])){
        networkClient.sendDisconnectMessage();
        // Time for networkClient.Send to deliver message
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        quit = true;
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
            networkClient.sendOnKeyPressedMessage(key);
        }
    }
}
