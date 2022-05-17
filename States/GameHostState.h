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
#include "Button.h"
#include <memory>

struct GameHostState : public GameState, std::enable_shared_from_this<GameHostState> {
    explicit GameHostState(std::shared_ptr<sf::RenderWindow> window,
                       std::map<std::string, sf::Keyboard::Key> supportedKey,
                       std::shared_ptr<std::vector<std::shared_ptr<State>>> states);
    public:
        sf::Font font;
        std::shared_ptr<NetworkServer> networkServer;
        std::shared_ptr<Button> startGameButton;
        void initPlayers();
        void updateInput(float dt);
        void update(float dt);
        void render(std::shared_ptr<sf::RenderTarget> target);
        void initButtons();
        void initFonts();

        int getNewPlayerId();
        // for NetworkServer
        void initFunctionsForNetworkServer();
};

#endif