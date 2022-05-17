#ifndef MY_TANKS_IN_LABIRINT_NETWORKCLIENT_H
#define MY_TANKS_IN_LABIRINT_NETWORKCLIENT_H

#include "inc/olc_network.h"
#include "inc/common.h"

class NetworkClient : public olc::net::client_interface<GameMessage> {
    int id;
    public:
        void setId(int newId);
        void sendDisconnectMessage();
};

#endif