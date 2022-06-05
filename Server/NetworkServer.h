#ifndef MY_TANKS_IN_LABIRINT_NETWORKSERVER_H
#define MY_TANKS_IN_LABIRINT_NETWORKSERVER_H

#include "inc/olc_network.h"
#include "inc/common.h"
#include <functional>
#include "Map.h"
#include <queue>
#include "../Serialization/proto/GameState.pb.h"

const int NEW_STATE_MESSAGE_SIZE = 500;
const int MAX_PLAYERS_NUMBER = 4;
const int MIN_PLAYERS_NUMBER = 1;

class NetworkServer : public olc::net::server_interface<GameMessage> {
    public:
        NetworkServer() = default;
        NetworkServer(uint16_t nPort);
        ~NetworkServer();

        std::function<std::pair<int, serialized::GameState>()> addPlayerFunc;
        std::function<serialized::GameState(int)> deletePlayerFunc;
        std::function<serialized::Map()> getGameMapFunc;
        std::function<int()> getPlayersNumberFunc;
        bool OnClientConnect(std::shared_ptr<olc::net::connection<GameMessage>> client);
        void OnClientValidated(std::shared_ptr<olc::net::connection<GameMessage>> client);
        void OnMessage(std::shared_ptr<olc::net::connection<GameMessage>> client, olc::net::message<GameMessage>& msg);
        void sendAllClientsNewGameState(serialized::GameState serializedState);
        void sendAllClientsNewGameMap(serialized::Map serializedMap);
        bool isGameStarted = false;
        void startGame();  
        std::queue<std::pair<int, int>> pressedKeysQueue;
        std::vector<bool> playersExisting;
};

#endif