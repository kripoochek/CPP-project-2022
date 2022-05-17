#ifndef MY_TANKS_IN_LABIRINT_GAMECLIENTSTATE_H
#define MY_TANKS_IN_LABIRINT_GAMECLIENTSTATE_H
#include "CollisionManager.h"
#include "GameState.h"
#include "Player.h"
#include "Bullet.h"
#include "Map.h"
#include "NetworkClient.h"
#include <deque>

struct GameClientState : public GameState {
    // Initialisation
    explicit GameClientState(std::shared_ptr<sf::RenderWindow> window,
                       std::map<std::string, sf::Keyboard::Key> supportedKey,
                       std::shared_ptr<std::vector<std::shared_ptr<State>>> states);
    NetworkClient networkClient;
    // Updates
    void updateInput(float dt);
    void update(float dt);

public:
    void initConnection();
};

#endif //MY_TANKS_IN_LABIRINT_GAMESTATE_H
