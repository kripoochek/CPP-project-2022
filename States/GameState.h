#ifndef MY_TANKS_IN_LABIRINT_GAMESTATE_H
#define MY_TANKS_IN_LABIRINT_GAMESTATE_H

#include "State.h"
#include "RoundState.h"
#include "NetworkClient.h"
#include "NetworkServer.h"

enum GameStateType {
    LOCAL, HOST, CLIENT
} ;

struct GameState : State {
    GameState(std::shared_ptr<sf::RenderWindow> window,
                       std::map<std::string, sf::Keyboard::Key> supportedKey,
                       std::shared_ptr<std::vector<std::shared_ptr<State>>> states,
                       int numOfRounds, const sf::Font &font, GameStateType type);

    // Updates
    void updateInput(float dt) final;
    void update(float dt) final;

    // Rendering
    void render(std::shared_ptr<sf::RenderTarget> target) final;
private:
    GameStateType type;
    std::shared_ptr<NetworkClient> networkClient;
    std::shared_ptr<NetworkServer> networkServer;

    std::vector<Result> scores;

    sf::Font font;

    void initKeybindings() final;

    int timer;
    int numOfRounds;
};

#endif //MY_TANKS_IN_LABIRINT_GAMESTATE_H
