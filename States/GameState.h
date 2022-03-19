#ifndef MY_TANKS_IN_LABIRINT_GAMESTATE_H
#define MY_TANKS_IN_LABIRINT_GAMESTATE_H

#include "State.h"
#include "Player.h"
#include "Map.h"
struct GameState : State {
    //Constructors/Destructors
    explicit GameState(std::shared_ptr<sf::RenderWindow> window,
                       std::map<std::string, sf::Keyboard::Key> supportedKey,
                       std::shared_ptr<std::vector<std::shared_ptr<State>>> states);
    //Funcions

    //Update
    void updateInput(float dt) final;
    void update(float dt) final;

    //Render
    void render(std::shared_ptr<sf::RenderTarget> target) final;
private:
    std::vector<std::shared_ptr<Player>> players;
    std::shared_ptr<Map> map;
    void initKeybinds() final;
    void initTextures();
    void initPlayers();
};

#endif //MY_TANKS_IN_LABIRINT_GAMESTATE_H
