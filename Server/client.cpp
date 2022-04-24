#include <iostream>
#include "inc/olc_network.h"
#include "inc/common.h"
#include <chrono>
#include <thread>
#include <memory>

class GameClient : public olc::net::client_interface<GameMessage> {
};

int main() {
    GameClient client;
    std::string str;
    if (client.Connect("127.0.0.1", 60000)) {
        std::thread([&]{
            while (client.IsConnected()) {
                while (!client.Incoming().empty()) {
                    auto msg = client.Incoming().pop_front().msg;
                    if (msg.header.id == GameMessage::NEW_GAME_STATE) {
                        char str[1000];
                        // std::unique_ptr<std::string> ptr;
                        msg >> str;
                        std::cout << "New game state: " << str << "\n";
                    }
                }
                std::this_thread::sleep_for(std::chrono::milliseconds(10));
            }
        }).detach();
        while (std::getline(std::cin, str)) {
            olc::net::message<GameMessage> msg;
            msg.header.id = GameMessage::ON_KEY_PRESSED;
            msg << str[0];
            client.Send(msg);
        }
    }
    return 0;
}