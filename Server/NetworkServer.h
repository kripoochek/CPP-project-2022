#ifndef MY_TANKS_IN_LABIRINT_NETWORKSERVER_H
#define MY_TANKS_IN_LABIRINT_NETWORKSERVER_H

#include "inc/olc_network.h"
#include "inc/common.h"
#include <functional>
#include "Map.h"
#include <map>
#include "../Serialization/proto/GameState.pb.h"

const int NEW_STATE_MESSAGE_SIZE = 25000;

class NetworkServer : public olc::net::server_interface<GameMessage> {
    public:
        NetworkServer() = default;
        NetworkServer(uint16_t nPort);
        ~NetworkServer();

        std::function<std::pair<int, serialized::GameState>()> addPlayerFunc;
        std::function<serialized::GameState(int)> deletePlayerFunc;
        bool OnClientConnect(std::shared_ptr<olc::net::connection<GameMessage>> client);
        void OnClientDisconnect(std::shared_ptr<olc::net::connection<GameMessage>> client);
        void OnClientValidated(std::shared_ptr<olc::net::connection<GameMessage>> client);
        void OnMessage(std::shared_ptr<olc::net::connection<GameMessage>> client, olc::net::message<GameMessage>& msg);
        bool isGameStarted = false;
        std::map<int, int> ids; // key: client id, value: player id   
};

#endif