#include "NetworkServer.h"
#include "inc/olc_network.h"
#include "inc/common.h"
#include "GameState.h"
#include <iostream>

NetworkServer::NetworkServer(uint16_t nPort) : olc::net::server_interface<GameMessage>(nPort){
};

NetworkServer::~NetworkServer() {
    olc::net::message<GameMessage> msg;
    msg.header.id = GameMessage::SERVER_STOP;
    MessageAllClients(msg);
    Stop();
}

bool NetworkServer::OnClientConnect(std::shared_ptr<olc::net::connection<GameMessage>> client) {
    return true;
}

void NetworkServer::OnClientDisconnect(std::shared_ptr<olc::net::connection<GameMessage>> client) {
    olc::net::message<GameMessage> newGameStateMsg;
    newGameStateMsg.header.id = GameMessage::NEW_GAME_STATE;   
    std::cout << ids[client->GetID()] << " ";
    serialized::GameState serializedGameState = deletePlayerFunc(ids[client->GetID()]);
    char char_array[NEW_STATE_MESSAGE_SIZE];
    serializedGameState.SerializeToArray(&char_array, NEW_STATE_MESSAGE_SIZE);
    newGameStateMsg << char_array;
    MessageAllClients(newGameStateMsg);
}

void NetworkServer::OnClientValidated(std::shared_ptr<olc::net::connection<GameMessage>> client) {
    std::pair<int, serialized::GameState> res = addPlayerFunc();
    ids[client->GetID()] = res.first;

    olc::net::message<GameMessage> newGameStateMsg;
    newGameStateMsg.header.id = GameMessage::NEW_GAME_STATE;   
    serialized::GameState serializedGameState = res.second;
    char char_array[NEW_STATE_MESSAGE_SIZE];
    serializedGameState.SerializeToArray(&char_array, NEW_STATE_MESSAGE_SIZE);
    newGameStateMsg << char_array;
    MessageAllClients(newGameStateMsg);
}

void NetworkServer::OnMessage(std::shared_ptr<olc::net::connection<GameMessage>> client, olc::net::message<GameMessage>& msg) {
    if (msg.header.id == GameMessage::ON_KEY_PRESSED) {
        char key;
        msg >> key;
        std::cout << client->GetID() << " pressed: " << key << "\n";
        olc::net::message<GameMessage> msg;
        msg.header.id = GameMessage::NEW_GAME_STATE;

        // GameStateSerializator gameStateSerializator(gameStatePtr);
        // serialized::GameState serializedGameState = gameStateSerializator.serialize();
        // std::string str;
        // char char_array[25000];
        // serializedGameState.SerializeToArray(&char_array, 25000);
        // msg << char_array;
        // MessageAllClients(msg);
    }
    if (msg.header.id == GameMessage::CLIENT_DISCONNECT) {
        int id;
        msg >> id;

        olc::net::message<GameMessage> newGameStateMsg;
        newGameStateMsg.header.id = GameMessage::NEW_GAME_STATE;   
        serialized::GameState serializedGameState = deletePlayerFunc(id);
        char char_array[NEW_STATE_MESSAGE_SIZE];
        serializedGameState.SerializeToArray(&char_array, NEW_STATE_MESSAGE_SIZE);
        newGameStateMsg << char_array;
        MessageAllClients(newGameStateMsg);
    }
}