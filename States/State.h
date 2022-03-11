#ifndef MY_TANKS_IN_LABIRINT_STATE_H
#define MY_TANKS_IN_LABIRINT_STATE_H

#include "Entity.h"

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
protected:
    std::shared_ptr<std::vector<std::shared_ptr<State>>> states;
    std::shared_ptr<sf::RenderWindow> window;
    std::map<std::string, sf::Keyboard::Key> supportedKeys;
    std::map<std::string, sf::Keyboard::Key> keybinds;
    bool quit;

    sf::Vector2i mousePosScreen;
    sf::Vector2i mousePosWindow;
    sf::Vector2f mousePosView;


    //Resources
    std::map<std::string, sf::Texture> textures;

    virtual void initKeybinds() = 0;
private:
};


#endif //MY_TANKS_IN_LABIRINT_STATE_H
