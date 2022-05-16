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

void NetworkServer::OnClientValidated(std::shared_ptr<olc::net::connection<GameMessage>> client) {
        olc::net::message<GameMessage> msg;
        msg.header.id = GameMessage::NEW_GAME_STATE;   

        // GameStateSerializator gameStateSerializator;
        // std::cout << getGameStatePtr()->players.size();
        // gameStateSerializator.serializeMap(gameStatePtr->map);
        // serialized::GameState serializedGameState = gameStateSerializator.serialize();
        std::string str;
        char char_array[25000];
        serializedGameState.SerializeToArray(&char_array, 25000);
        msg << char_array;
        client->Send(msg);
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
}