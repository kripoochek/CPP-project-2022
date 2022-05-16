#ifndef MY_TANKS_IN_LABIRINT_GAMEHOSTSTATE_H
#define MY_TANKS_IN_LABIRINT_GAMEHOSTSTATE_H

#include "CollisionManager.h"
#include "State.h"
#include "GameState.h"
#include "Player.h"
#include "Bullet.h"
#include "Map.h"
#include "NetworkServer.h"
#include <deque>
#include <memory>

struct GameHostState : public GameState, std::enable_shared_from_this<GameHostState> {
    explicit GameHostState(std::shared_ptr<sf::RenderWindow> window,
                       std::map<std::string, sf::Keyboard::Key> supportedKey,
                       std::shared_ptr<std::vector<std::shared_ptr<State>>> states);
    public:
        std::shared_ptr<NetworkServer> networkServer;
        void update(float dt);
};

#endif