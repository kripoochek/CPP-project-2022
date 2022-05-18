#include "Game.h"

Game::Game() {
    initVariables();
    initWindow();
    initKeys();
    initStates();
}

void Game::endApplication() {
    std::cout << "End Application!\n";
}

void Game::updateDt() { dt = dtClock.restart().asSeconds();}

void Game::updateSFMLEvents() {
    while(window->pollEvent(sfEvent)){
        
        if (sfEvent.type == sf::Event::GainedFocus && !states->empty()) {
            states->back()->isWindowFocused = true;
        }
        if (sfEvent.type == sf::Event::LostFocus && !states->empty()) {
            states->back()->isWindowFocused = false;
        }
        if (sfEvent.type == sf::Event::Closed){
            window->close();
        }
    }
}

void Game::update() {
    updateSFMLEvents();

    if (states->empty()){
        endApplication();
        window->close();
        return;
    }
    states->back()->update(dt);
    if (states->back()->getQuit()){
        states->back()->endState();
        states->pop_back();
    }
}

void Game::render() {
    window->clear();
    if (!states->empty()){
        states->back()->render(window);
    }

    window->display();
}

void Game::run() {
    while(window->isOpen()){
        updateDt();
        update();
        render();
    }
}

void Game::initVariables() {
    fullscreen = false;
    dt = 0;
}

void Game::initWindow() {
    std::ifstream file("../Config/window.ini");

    std::string title = "Furious Tanks Battle";
    sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
    int framerate_limit = 120;
    bool vertical_sync_enabled = false;
    int antialiasing_level = 0;


    if (file.is_open()){
        std::getline(file, title);
        file >> window_bounds.width >> window_bounds.height;
        file >> fullscreen;
        file >> framerate_limit;
        file >> vertical_sync_enabled;
        file >> antialiasing_level;
    }

    windowSettings.antialiasingLevel = antialiasing_level;

    if (fullscreen){
        window = std::make_shared<sf::RenderWindow>(window_bounds, title, sf::Style::Fullscreen, windowSettings);
    }
    else{
        window = std::make_shared<sf::RenderWindow>(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, windowSettings);
    }

    window->setFramerateLimit(framerate_limit);
    window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initStates() {
    states = std::make_shared<std::vector<std::shared_ptr<State>>>();
    states->push_back(std::make_shared<MainMenuState>(window, supportedKeys, states));

    // TODO:
    // states->push_back(std::make_shared<GameState>(window, supportedKeys, states));
}

void Game::initKeys() {
    std::ifstream file("../Config/supported_keys.ini");
    if (file.is_open()){
        std::string key;
        int key_value = 0;
        while(file >> key >> key_value){
            supportedKeys[key] = static_cast<sf::Keyboard::Key>(key_value);
        }
    }
}






