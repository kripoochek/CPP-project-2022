#ifndef MY_TANKS_IN_LABIRINT_GAMESTATE_H
#define MY_TANKS_IN_LABIRINT_GAMESTATE_H
#include "CollisionManager.h"
#include "State.h"
#include "Player.h"
#include "Bullet.h"
#include "Map.h"
#include <deque>

struct GameState : State {
    // Initialisation
    explicit GameState(std::shared_ptr<sf::RenderWindow> window,
                       std::map<std::string, sf::Keyboard::Key> supportedKey,
                       std::shared_ptr<std::vector<std::shared_ptr<State>>> states);

    // Updates
    void updateInput(float dt) final;
    void update(float dt) final;

    // Rendering
    void render(std::shared_ptr<sf::RenderTarget> target) final;
private:
    // Texture assets
    std::shared_ptr<GameTextures> textures;
    std::shared_ptr<CollisionManager> collisionManager;
    std::deque<std::shared_ptr<Bullet>> bullets;
    std::vector<std::shared_ptr<Player>> players;
    std::shared_ptr<Map> map;

    void initKeybindings() final;
    void initTextures();
    void initPlayers();
};

#endif //MY_TANKS_IN_LABIRINT_GAMESTATE_H
