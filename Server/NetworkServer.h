#ifndef MY_TANKS_IN_LABIRINT_NETWORKCLIENT_H
#define MY_TANKS_IN_LABIRINT_NETWORKCLIENT_H

#include "inc/olc_network.h"
#include "inc/common.h"
#include "GameHostState.h"


class NetworkServer : public olc::net::server_interface<GameMessage> {
    public:
        std::shared_ptr<GameHostState> gameStatePtr;
        NetworkServer(uint16_t nPort, std::shared_ptr<GameHostState> ptr);
        ~NetworkServer();

        bool OnClientConnect(std::shared_ptr<olc::net::connection<GameMessage>> client);
        void OnClientValidated(std::shared_ptr<olc::net::connection<GameMessage>> client);
        void OnMessage(std::shared_ptr<olc::net::connection<GameMessage>> client, olc::net::message<GameMessage>& msg);

};

#endif