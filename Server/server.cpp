#include <iostream>
#include "inc/olc_network.h"
#include "dest/addressbook.pb.h"
#include "inc/common.h"
#include <memory>
#include <functional>
#include <thread>
#include <chrono>
#include <sstream>
#include <ctime>
#include <iomanip>
#include "../Game.h"
#include "../States/GameState.h"
#include <Box2D/Box2D.h>
#include "../Serialization/GameStateSerializator.h"

std::string testProtobuf() {
    tutorial::Person person;
    person.set_id(1);
    person.set_email("aaa@mail.ru");
    person.set_name("Guga");
    std::string out;
    person.SerializeToString(&out);
    return out;
}

std::string time_in_HH_MM_SS_MMM()
{
    using namespace std::chrono;

    // get current time
    auto now = system_clock::now();

    // get number of milliseconds for the current second
    // (remainder after division into seconds)
    auto ms = duration_cast<milliseconds>(now.time_since_epoch()) % 1000;

    // convert to std::time_t in order to convert to std::tm (broken time)
    auto timer = system_clock::to_time_t(now);

    // convert to broken time
    std::tm bt = *std::localtime(&timer);

    std::ostringstream oss;

    oss << std::put_time(&bt, "%H:%M:%S"); // HH:MM:SS
    oss << '.' << std::setfill('0') << std::setw(3) << ms.count();

    return oss.str();
}

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
                std::cout << client->GetID() << " pressed: " << key << ",time: " << time_in_HH_MM_SS_MMM() << "\n";
                olc::net::message<GameMessage> msg;
                msg.header.id = GameMessage::NEW_GAME_STATE;
                std::string str = testProtobuf();
                char char_array[1000];
                strcpy(char_array, str.c_str());
                msg << char_array;
                MessageAllClients(msg);
            }
        }
};

int main() {
    Game game;
    std::thread([&]{
        // GameStateSerializator gameStateSerializator(game.states->back());
        // gameStateSerializator.getSerializedPlayer();

        // GameServer server(60000);
        // server.Start();
        // while (true) {
        //     server.Update(-1, true);
        // }
    }).detach();
    auto gameState = std::make_shared<GameState>(game.window, game.supportedKeys, game.states);
    GameStateSerializator gameStateSerializator(gameState);
    gameStateSerializator.serialize();
    // game.run();
    return 0;
}