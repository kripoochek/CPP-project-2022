#ifndef MY_TANKS_IN_LABIRINT_MAINMENUSTATE_H
#define MY_TANKS_IN_LABIRINT_MAINMENUSTATE_H

#include "GameState.h"
#include "Button.h"

#include <sstream>

struct MainMenuState : State {
    //Constructors/Destructors
    explicit MainMenuState(std::shared_ptr<sf::RenderWindow> window,
    std::map<std::string, sf::Keyboard::Key> supportedKey,
    std::shared_ptr<std::vector<std::shared_ptr<State>>> states);

    // Updates
    void updateInput(float dt) final;
    void updateButtons();
    void update(float dt) final;

    // Rendering
    void renderButtons(sf::RenderTarget &target);
    void render(std::shared_ptr<sf::RenderTarget> target) final;
private:
    sf::RectangleShape backgroundLayout;
    sf::Font font;

    // Texture assets
    std::shared_ptr<GameTextures> textures;

    std::map<std::string, std::shared_ptr<Button> > buttons;

    void initVariables();
    void initBackground();
    void initKeybindings() final;
    void initFonts();
    void initButtons();
};


#endif //MY_TANKS_IN_LABIRINT_MAINMENUSTATE_H
