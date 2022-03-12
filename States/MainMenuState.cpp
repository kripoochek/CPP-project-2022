#include "MainMenuState.h"

MainMenuState::MainMenuState(std::shared_ptr<sf::RenderWindow> window,
                     std::map<std::string, sf::Keyboard::Key> supportedKey,
                     std::shared_ptr<std::vector<std::shared_ptr<State>>> states) :
        State(std::move(window), std::move(supportedKey), std::move(states)) {

    initVariables();
    initBackground();
    initFonts();
    initKeybinds();
    initButtons();


    background.setSize(sf::Vector2f(this->window->getSize()));
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

    target->draw(background);

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

void MainMenuState::initKeybinds() {
    std::ifstream file("../Config/mainmenustate_keybinds.ini");

    if (file.is_open()){
        std::string key;
        std::string key2;
        while(file >> key >> key2){
            keybinds[key] = supportedKeys[key2];
        }
    }
}

void MainMenuState::initFonts() {
    if (!font.loadFromFile("../Fonts/Le chant des Albatros.ttf")){
        std::cout << "Font don't open!\n";
    }
}

void MainMenuState::initButtons() {
    buttons["GAME_STATE"] = std::make_shared<Button>(300, 480, 150, 50,
                                             font, "New Game",
                                             sf::Color(70, 70, 70, 200),
                                             sf::Color(150, 150, 150, 255),
                                             sf::Color(20, 20, 20, 200));

    buttons["SETTINGS"] = std::make_shared<Button>(300, 580, 150, 50,
                                                     font, "Settings",
                                                     sf::Color(70, 70, 70, 200),
                                                     sf::Color(150, 150, 150, 255),
                                                     sf::Color(20, 20, 20, 200));

    buttons["EXIT_STATE"] = std::make_shared<Button>(300, 650, 150, 50,
                                                     font, "Quit",
                                                     sf::Color(100, 100, 100, 200),
                                                     sf::Color(150, 150, 150, 255),
                                                     sf::Color(20, 20, 20, 200));
}

void MainMenuState::initBackground() {
    background.setSize(sf::Vector2f(window->getSize().x,
                                    window->getSize().y));
    if (!backgroundTexture.loadFromFile("../Resources/Images/Backgrounds/mainmenu.png")){
        throw std::exception();
    }
    background.setTexture(&backgroundTexture);
}

void MainMenuState::initVariables() {

}



