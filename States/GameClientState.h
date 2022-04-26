#ifndef MY_TANKS_IN_LABIRINT_GAMESTATECLIENT_H
#define MY_TANKS_IN_LABIRINT_GAMESTATECLIENT_H
#include "CollisionManager.h"
#include "State.h"
#include "Player.h"
#include "Bullet.h"
#include "Map.h"
#include "NetworkClient.cpp"
#include <deque>

struct GameClientState : State {
    // Initialisation
    explicit GameClientState(std::shared_ptr<sf::RenderWindow> window,
                       std::map<std::string, sf::Keyboard::Key> supportedKey,
                       std::shared_ptr<std::vector<std::shared_ptr<State>>> states);
    NetworkClient networkClient;
    

    // Updates
    void updateInput(float dt) final;
    void update(float dt) final;

    // Rendering
    void render(std::shared_ptr<sf::RenderTarget> target) final;
public:
    // Texture assets
    std::shared_ptr<GameTextures> textures;

    void initKeybindings() final;
    void initTextures();
    void initConnection() final;
};

#endif //MY_TANKS_IN_LABIRINT_GAMESTATE_H
