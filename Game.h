#ifndef MY_TANKS_IN_LABIRINT_GAME_H
#define MY_TANKS_IN_LABIRINT_GAME_H

#include "MainMenuState.h"

struct Game {
    //Constructors/Destructors
    Game();

    //Functions

    static void endApplication();

    //Update
    void updateDt();
    void updateSFMLEvents();
    void update();

    //Render
    void render();

    //Core
    void run();

private:
    //Variables
    std::shared_ptr<sf::RenderWindow> window;
    sf::Event sfEvent{};
    std::vector<sf::VideoMode> videoModes;
    sf::ContextSettings windowSettings;
    bool fullscreen{};

    sf::Clock dtClock;
    float dt{};

    std::shared_ptr<std::vector<std::shared_ptr<State>>> states;
    std::map<std::string, sf::Keyboard::Key> supportedKeys;

    //Initialization
    void initVariables();
    void initWindow();
    void initStates();
    void initKeys();
};

#endif //MY_TANKS_IN_LABIRINT_GAME_H