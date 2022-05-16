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

struct GameHostState : GameState {
    explicit GameHostState(std::shared_ptr<sf::RenderWindow> window,
                       std::map<std::string, sf::Keyboard::Key> supportedKey,
                       std::shared_ptr<std::vector<std::shared_ptr<State>>> states);
    
    private:
        NetworkServer networkServer;

};

#endif