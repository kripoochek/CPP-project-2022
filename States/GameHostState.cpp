#include "GameHostState.h"
#include "GameState.h"
#include "NetworkServer.h"
#include "GameStateSerializator.h"

GameHostState::GameHostState(std::shared_ptr<sf::RenderWindow> window,
                       std::map<std::string, sf::Keyboard::Key> supportedKey,
                       std::shared_ptr<std::vector<std::shared_ptr<State>>> states) : GameState(
                           std::move(window), std::move(supportedKey), std::move(states)
                       ), networkServer(std::make_shared<NetworkServer>(60000)) {
    initFonts();
    initButtons();
    initPlayers();
    initFunctionsForNetworkServer();
    networkServer->Start();
};

void GameHostState::updateInput(float dt) {
    if (sf::Keyboard::isKeyPressed(keybindings["CLOSE"]) && isWindowFocused){
        quit = true;
    }

    if (!networkServer->isGameStarted) { return; }
    
    if (sf::Keyboard::isKeyPressed(keybindings["ATTACK1"])){
        players[0]->attack(bullets, textures->Bullet, dt);
    }
    if (sf::Keyboard::isKeyPressed(keybindings["MOVE_LEFT1"])){
        players[0]->rotate(false, dt);
    }
    if (sf::Keyboard::isKeyPressed(keybindings["MOVE_RIGHT1"])){
        players[0]->rotate(true, dt);
    }
    if (sf::Keyboard::isKeyPressed(keybindings["MOVE_UP1"])){
        players[0]->move(true, dt);
    }
    if (sf::Keyboard::isKeyPressed(keybindings["MOVE_DOWN1"])){
        players[0]->move(false, dt);
    }
}

void GameHostState::update(float dt) {
    GameState::update(dt);
    networkServer->Update(-1, true);
    startGameButton->update(mousePosView);

    if (startGameButton->isPressed()) {
        std::cout << "Start game!";
    }
}

void GameHostState::initPlayers() {
    map = std::make_shared<Map>(sf::Vector2f(200,50),
                               textures->Box,
                               textures->VerticalBorder,
                               textures->HorizontalBorder);
    players.clear(); // because of GameState constructor
    players.push_back( std::make_shared<Player>(250, 100, 5, 0, textures->FirstPlayerIdle));
    collisionManager = std::make_shared<CollisionManager>(map, players);
}

void GameHostState::render(std::shared_ptr<sf::RenderTarget> target) {
    if (!networkServer->isGameStarted && players.size() >= 2) {
        startGameButton->render(*target);    
    }
    GameState::render(target);
}

void GameHostState::initFonts() {
    if (!font.loadFromFile("../Fonts/SuperMario256.ttf")){
        std::cout << "Font don't open!\n";
    }
}

void GameHostState::initButtons() {
    const sf::Color idleColor(70, 70, 70, 0);
    const sf::Color hoverColor(150, 150, 150, 0);
    const sf::Color activeColor(20, 20, 20, 0);

    const sf::Color textIdleColor(100, 100, 100, 225);
    const sf::Color textHoverColor(255, 255, 255, 250);
    const sf::Color textActiveColor(20, 20, 20, 50);

    startGameButton = std::make_shared<Button>(90, 30, 100, 50,
                                                font, "Start Game", 20,
                                                textIdleColor, textHoverColor, textActiveColor,
                                                idleColor, hoverColor, activeColor);
}

void GameHostState::initFunctionsForNetworkServer() {
    networkServer->addPlayerFunc = [&](){
        int id = getNewPlayerId();
        auto player = std::make_shared<Player>(250 + 100 * id, 100, 5, 0, textures->getPlayerTextureById(id));
        if (id == players.size()) { players.push_back(player); }
        else { players[id] = player; }  
        return std::make_pair(id, GameStateSerializator::serialize(shared_from_this()));
    };
    networkServer->deletePlayerFunc = [&](int id) {
        std::cout << players.size();
        players[id] = nullptr;
        return GameStateSerializator::serialize(shared_from_this());
    };
}

int GameHostState::getNewPlayerId() {
    for (int i = 0; i < players.size(); i++) {
        if (players[i] == nullptr) { return i; }
    }
    return players.size();
}