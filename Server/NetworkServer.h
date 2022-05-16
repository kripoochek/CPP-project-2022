#ifndef MY_TANKS_IN_LABIRINT_NETWORKSERVER_H
#define MY_TANKS_IN_LABIRINT_NETWORKSERVER_H

#include "inc/olc_network.h"
#include "inc/common.h"
#include <functional>
#include "Map.h"
#include "../Serialization/proto/GameState.pb.h"

class NetworkServer : public olc::net::server_interface<GameMessage> {
    public:
        serialized::GameState serializedGameState;
        NetworkServer() = default;
        NetworkServer(uint16_t nPort);
        ~NetworkServer();

        bool OnClientConnect(std::shared_ptr<olc::net::connection<GameMessage>> client);
        void OnClientValidated(std::shared_ptr<olc::net::connection<GameMessage>> client);
        void OnMessage(std::shared_ptr<olc::net::connection<GameMessage>> client, olc::net::message<GameMessage>& msg);

};

#endif