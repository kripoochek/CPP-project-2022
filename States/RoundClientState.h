#ifndef MY_TANKS_IN_LABIRINT_ROUNDCLIENTSTATE_H
#define MY_TANKS_IN_LABIRINT_ROUNDCLIENTSTATE_H
#include "CollisionManager.h"
#include "GameState.h"
#include "Player.h"
#include "Bullet.h"
#include "Map.h"
#include "NetworkClient.h"
#include <deque>

struct RoundClientState : public RoundState {
    // Initialisation
    explicit RoundClientState(std::shared_ptr<sf::RenderWindow> window,
                       std::map<std::string, sf::Keyboard::Key> supportedKey,
                       std::shared_ptr<std::vector<std::shared_ptr<State>>> states,
                       std::vector<Result> &scores,
                       std::shared_ptr<NetworkClient> networkClient);
    std::shared_ptr<NetworkClient> networkClient;
    // Updates
    void updateInput(float dt);
    void update(float dt);
};

#endif //MY_TANKS_IN_LABIRINT_GAMESTATE_H