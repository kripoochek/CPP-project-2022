#include "GameClientState.h"
#include "NetworkClient.h"

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
    networkClient.connect("127.0.0.1", 60000));
}

void GameClientState::update() {
    if (networkClient.IsConnected()) {
        while (!client.Incoming().empty()) {
            auto msg = client.Incoming().pop_front().msg;
            if (msg.header.id == GameMessage::NEW_GAME_STATE) {
                // std::vector<std::vector<Box>> boxes;
                // char str[25000];
                // msg >> str;
                // serialized::GameState gs;
                // boxes.resize(gs.map().rowsnumber(), std::vector<Box>(gs.map().columnsnumber()));
                // gs.ParseFromArray(str, 10000);
                // std::cout << "New game state: " << gs.map().rowsnumber() << ", time: " << time_in_HH_MM_SS_MMM() << "\n";
                // for (int i = 0; i < gs.map().rowsnumber(); i++) {
                //     auto mapRow = gs.map().rows().at(i);
                //     for (int j = 0; j < gs.map().columnsnumber(); j++) {
                        // boxes[i][j] = Box()
                        // std::cout << mapRow.boxes().at(j).x() << " ";
                    // }
                    // std::cout << '\n';
                // }
            }
            if (msg.header.id == GameMessage::SERVER_STOP) {
                client.Disconnect();
            }
        }
    } else {
        // TODO: Go to menu
    }
}