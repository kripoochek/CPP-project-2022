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

// std::string time_in_HH_MM_SS_MMM()
// {
//     using namespace std::chrono;

//     // get current time
//     auto now = system_clock::now();

//     // get number of milliseconds for the current second
//     // (remainder after division into seconds)
//     auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

//     // convert to std::time_t in order to convert to std::tm (broken time)
//     auto timer = system_clock::to_time_t(now);

//     // convert to broken time
//     std::tm bt = *std::localtime(&timer);

//     std::ostringstream oss;

//     oss << std::put_time(&bt, "%H:%M:%S"); // HH:MM:SS
//     oss << '.' << std::setfill('0') << std::setw(3) << ms.count();

//     return oss.str();
// }

void GameClientState::update(float dt) {
    updateInput(dt);
    if (networkClient.IsConnected()) {
        while (!networkClient.Incoming().empty()) {
            auto msg = networkClient.Incoming().pop_front().msg;
            std::cout << msg.size();
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
        // TODO: Go to menu
        quit = true;
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
    if (sf::Keyboard::isKeyPressed(keybindings["CLOSE"])){
        quit = true;
    }
}