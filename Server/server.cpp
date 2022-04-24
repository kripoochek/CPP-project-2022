#include <iostream>
#include "inc/olc_network.h"
#include "inc/common.h"
#include <memory>
#include <functional>

class GameServer : public olc::net::server_interface<GameMessage> {
    public:
        GameServer(uint16_t nPort) : olc::net::server_interface<GameMessage>(nPort){};
    protected:
        bool OnClientConnect(std::shared_ptr<olc::net::connection<GameMessage>> client) override
        {
            return true;
        }
        void OnClientValidated(std::shared_ptr<olc::net::connection<GameMessage>> client) override
        {
            // Client passed validation check, so send them a message informing
            // them they can continue to communicate
            olc::net::message<GameMessage> msg;
            msg.header.id = GameMessage::CLIENT_ACCEPTED;
            client->Send(msg);
        }
        void OnClientDisconnect(std::shared_ptr<olc::net::connection<GameMessage>> client) override
        {
            if (client)
            {
                std::cout << "Client disconnected: " << client->GetID() << "\n";
            }
        }
        void OnMessage(std::shared_ptr<olc::net::connection<GameMessage>> client, olc::net::message<GameMessage>& msg) override
        {
            if (msg.header.id == GameMessage::ON_KEY_PRESSED) {
                char key;
                msg >> key;
                std::cout << client->GetID() << " pressed: " << key << "\n";
                olc::net::message<GameMessage> msg;
                msg.header.id = GameMessage::NEW_GAME_STATE;
                // char str[1000];
                // str[0] = 'H';
                // str[1] = 'e';
                // str[2] = 'l';
                std::string str = "Hello world!";
                // auto ptr = std::make_unique<std::string>(str);
                char char_array[1000];
                strcpy(char_array, str.c_str());
                msg << char_array;
                MessageAllClients(msg);
            }
        }
};

int main() {
    GameServer server(60000);
    server.Start();
    while (true) {
        server.Update(-1, true);
    }
    return 0;
}