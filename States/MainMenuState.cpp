#include "MainMenuState.h"

MainMenuState::MainMenuState(std::shared_ptr<sf::RenderWindow> window,
                     std::map<std::string, sf::Keyboard::Key> supportedKey,
                     std::shared_ptr<std::vector<std::shared_ptr<State>>> states) :
        State(std::move(window), std::move(supportedKey), std::move(states)) {

    initVariables();
    initBackground();
    initFonts();
    initKeybindings();
    initButtons();


    backgroundLayout.setSize(sf::Vector2f(this->window->getSize()));
}

void MainMenuState::updateInput(float dt) {

}

void MainMenuState::updateButtons() {
    for (auto &[name, button]: buttons){
        button->update(mousePosView);
    }

    if (buttons["GAME_STATE"]->isPressed()){
        states->push_back(std::make_shared<GameState>(window, supportedKeys, states));
    }
    if (buttons["EXIT_STATE"]->isPressed()){
        quit = true;
    }
}

void MainMenuState::update(float dt) {
    updateMousePositions();
    updateInput(dt);
    updateButtons();
}


void MainMenuState::renderButtons(std::shared_ptr<sf::RenderTarget> target) {
    for (auto &[name, button]: buttons){
        button->render(target);
    }
}

void MainMenuState::render(std::shared_ptr<sf::RenderTarget> target) {
    if (!target){ target = window;}

    target->draw(backgroundLayout);

    renderButtons(target);

    //REMOVE LATER!!
    sf::Text mouseText;
    mouseText.setPosition(mousePosView.x, mousePosView.y - 20);
    mouseText.setFont(font);
    mouseText.setCharacterSize(12);
    std::stringstream ss;
    ss << mousePosView.x << ' ' << mousePosView.y;
    mouseText.setString(ss.str());

    target->draw(mouseText);
}

void MainMenuState::initKeybindings() {
    std::ifstream file("../Config/mainmenustate_keybinds.ini");

    if (file.is_open()){
        std::string key;
        std::string key2;
        while(file >> key >> key2){
            keybindings[key] = supportedKeys[key2];
        }
    }
}

void MainMenuState::initFonts() {
    if (!font.loadFromFile("../Fonts/SuperMario256.ttf")){
        std::cout << "Font don't open!\n";
    }
}

void MainMenuState::initButtons() {
    const sf::Color idleColor(70, 70, 70, 0);
    const sf::Color hoverColor(150, 150, 150, 0);
    const sf::Color activeColor(20, 20, 20, 0);

    const sf::Color textIdleColor(100, 100, 100, 225);
    const sf::Color textHoverColor(255, 255, 255, 250);
    const sf::Color textActiveColor(20, 20, 20, 50);

    const uint btnWidth = 150, btnHeight = 50;
    const uint initialX = this->window->getSize().x / 4, initialY = this->window->getSize().y / 3;
    const uint btnPadding = btnHeight + 25;

    buttons["GAME_STATE"] = std::make_shared<Button>(initialX, initialY, btnWidth, btnHeight,
                                                     font, "New Game", 50,
                                                     textIdleColor, textHoverColor, textActiveColor,
                                                     idleColor, hoverColor, activeColor);

    buttons["SETTINGS"] = std::make_shared<Button>(initialX, initialY + btnPadding, btnWidth, btnHeight,
                                                   font, "Settings", 50,
                                                   textIdleColor, textHoverColor, textActiveColor,
                                                   idleColor, hoverColor, activeColor);

    buttons["EXIT_STATE"] = std::make_shared<Button>(initialX, initialY + 2 * btnPadding, btnWidth, btnHeight,
                                                     font, "Quit", 50,
                                                     textIdleColor, textHoverColor, textActiveColor,
                                                     idleColor, hoverColor, activeColor);
}

void MainMenuState::initBackground() {
    textures = std::make_shared<GameTextures>();
    backgroundLayout.setSize(sf::Vector2f(window->getSize().x,window->getSize().y));
    backgroundLayout.setTexture(&textures->MenuBackground);
}

void MainMenuState::initVariables() {

}



