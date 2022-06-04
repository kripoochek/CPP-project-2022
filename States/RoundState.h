#ifndef MY_TANKS_IN_LABIRINT_ROUNDSTATE_H
#define MY_TANKS_IN_LABIRINT_ROUNDSTATE_H

#include <Box2D/Box2D.h>
#include <deque>

#include "CollisionManager.h"
#include "State.h"
#include "Player.h"
#include "Bullet.h"
#include "Map.h"

struct Result {
    Result(float x, float y, const sf::Font& font, const std::string& prefText, int characterSize, sf::Color textColor);

    void render(sf::RenderTarget &target);

    int wins;
    int kills;
private:
    sf::Text text;
    sf::Color textColor;

    std::string prefText;
};

struct RoundState : State {
    // Initialisation
    RoundState(std::shared_ptr<sf::RenderWindow> window,
               std::map<std::string, sf::Keyboard::Key> supportedKey,
               std::shared_ptr<std::vector<std::shared_ptr<State>>> states,
               std::vector<Result> &scores,
               bool renderOnStart);

    // Updates
    void updateInput(float dt);
    void update(float dt);

    // Getters
    std::vector<std::shared_ptr<Player>> getPlayers();
    std::shared_ptr<Map> getMap();
    std::set<std::pair<int, std::shared_ptr<Bullet>>> getBullets();

    // Rendering
    void render(std::shared_ptr<sf::RenderTarget> target);

    sf::Font font;
    void initFonts();

protected:
    bool endOfRaund;
    bool renderOnStart;
    std::vector<Result> &scores;

    // Texture assets
    std::shared_ptr<GameTextures> textures;
    std::shared_ptr<CollisionManager> collisionManager;
    std::set<std::pair<int, std::shared_ptr<Bullet>>> bullets;
    std::vector<std::shared_ptr<Player>> players;
    std::shared_ptr<Map> map;

    std::shared_ptr<b2World> world;

    void initKeybindings() final;
    void initTextures();
    void initPlayers();
    void initWorld();
};

#endif //MY_TANKS_IN_LABIRINT_ROUNDSTATE_H
