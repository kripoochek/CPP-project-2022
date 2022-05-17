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
    return (getPlayersNumberFunc() < MAX_PLAYERS_NUMBER);
}

void NetworkServer::OnClientValidated(std::shared_ptr<olc::net::connection<GameMessage>> client) {
    std::pair<int, serialized::GameState> res = addPlayerFunc();

    olc::net::message<GameMessage> clientConnectedMsg;
    clientConnectedMsg.header.id = GameMessage::CLIENT_CONNECTED;
    clientConnectedMsg << res.first;
    client->Send(clientConnectedMsg);

    sendAllClientsNewGameState(res.second);
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
    if (msg.header.id == GameMessage::CLIENT_DISCONNECTED) {
        int id;
        msg >> id;
        sendAllClientsNewGameState(deletePlayerFunc(id));
    }
}

void NetworkServer::startGame() {
    if (getPlayersNumberFunc() >= MIN_PLAYERS_NUMBER && getPlayersNumberFunc() <= MAX_PLAYERS_NUMBER) {
        isGameStarted = true;
    }
}

void NetworkServer::sendAllClientsNewGameState(serialized::GameState serializedState) {
    olc::net::message<GameMessage> newGameStateMsg;
    newGameStateMsg.header.id = GameMessage::NEW_GAME_STATE;   
    char char_array[NEW_STATE_MESSAGE_SIZE];
    serializedState.SerializeToArray(&char_array, NEW_STATE_MESSAGE_SIZE);
    newGameStateMsg << char_array;
    MessageAllClients(newGameStateMsg);
}