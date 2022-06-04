#ifndef MY_TANKS_IN_LABIRINT_ROUNDHOSTSTATE_H
#define MY_TANKS_IN_LABIRINT_ROUNDHOSTSTATE_H

#include "CollisionManager.h"
#include "State.h"
#include "RoundState.h"
#include "Player.h"
#include "Bullet.h"
#include "Map.h"
#include "NetworkServer.h"
#include <deque>
#include "Button.h"
#include <memory>

struct RoundHostState : public RoundState, std::enable_shared_from_this<RoundHostState> {
    explicit RoundHostState(std::shared_ptr<sf::RenderWindow> window,
                       std::map<std::string, sf::Keyboard::Key> supportedKey,
                       std::shared_ptr<std::vector<std::shared_ptr<State>>> states,
                       std::vector<Result> &scores,
                       std::shared_ptr<NetworkServer> networkServer);
    public:
        std::shared_ptr<NetworkServer> networkServer;
        void initPlayers();
        void updateInput(float dt);
        void update(float dt);
        void render(std::shared_ptr<sf::RenderTarget> target);

        int getNewPlayerId();
        // for NetworkServer
        void initFunctionsForNetworkServer();
};

#endif