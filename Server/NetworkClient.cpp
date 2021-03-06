#include "inc/olc_network.h"
#include "inc/common.h"
#include "NetworkClient.h"

void NetworkClient::sendDisconnectMessage() {
    olc::net::message<GameMessage> msg;
    msg.header.id = GameMessage::CLIENT_DISCONNECTED;
    msg << id;
    Send(msg);
}

void NetworkClient::sendOnKeyPressedMessage(int key) {
    olc::net::message<GameMessage> msg;
    msg.header.id = GameMessage::ON_KEY_PRESSED;
    msg << id << key;
    Send(msg);
}

void NetworkClient::setId(int newId) {
    id = newId;
}