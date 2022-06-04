#ifndef MY_TANKS_IN_LABIRINT_STATE_H
#define MY_TANKS_IN_LABIRINT_STATE_H

#include "Entity.h"
#include "GameTextures.h"

struct State {
    //Constructors/Destructors
    State(std::shared_ptr<sf::RenderWindow> window,
          std::map<std::string, sf::Keyboard::Key> supportedKey,
          std::shared_ptr<std::vector<std::shared_ptr<State>>> states);

    //Functions

    [[nodiscard]] bool getQuit() const;

    void endState();

    //Update
    virtual void updateMousePositions();
    virtual void updateInput(float dt) = 0;
    virtual void update(float dt) = 0;

    //Render
    virtual void render(std::shared_ptr<sf::RenderTarget> target) = 0;

    bool isWindowFocused = true;
protected:
    bool quit;

    std::shared_ptr<std::vector<std::shared_ptr<State>>> states;
    std::shared_ptr<sf::RenderWindow> window;
    std::map<std::string, sf::Keyboard::Key> supportedKeys;
    std::map<std::string, sf::Keyboard::Key> keybindings;

    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;

    virtual void initKeybindings() = 0;
private:
};


#endif //MY_TANKS_IN_LABIRINT_STATE_H
