#include "RoundState.h"

RoundState::RoundState(std::shared_ptr<sf::RenderWindow> window,
                       std::map<std::string, sf::Keyboard::Key> supportedKey,
                       std::shared_ptr<std::vector<std::shared_ptr<State>>> states, std::vector<Result> &scores, bool renderOnStart) :
        State(std::move(window), std::move(supportedKey), std::move(states)), scores(scores), renderOnStart(renderOnStart) {

    initWorld();
    initTextures();
    initKeybindings();
    initPlayers();

    if (renderOnStart) {
        render(this->window);
        this->window->display();
        sf::sleep(sf::milliseconds(500));
    }
}

void RoundState::updateInput(float dt) {
    //Update player input
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

    if (sf::Keyboard::isKeyPressed(keybindings["ATTACK2"])){
        players[1]->attack(bullets, textures->Bullet, dt);
    }
    if (sf::Keyboard::isKeyPressed(keybindings["MOVE_LEFT2"])){
        players[1]->rotate(false, dt);
    }
    if (sf::Keyboard::isKeyPressed(keybindings["MOVE_RIGHT2"])){
        players[1]->rotate(true, dt);
    }
    if (sf::Keyboard::isKeyPressed(keybindings["MOVE_UP2"])){
        players[1]->move(true, dt);
    }
    if (sf::Keyboard::isKeyPressed(keybindings["MOVE_DOWN2"])){
        players[1]->move(false, dt);
    }

    if (sf::Keyboard::isKeyPressed(keybindings["CLOSE"])){
        quit = true;
    }
}

void RoundState::update(float dt) {
    world->Step(1/60.f, 8, 3);
    updateMousePositions();
    updateInput(dt);

   //collisionManager->update(dt);

    for (auto i = bullets.begin(); i != bullets.end();){
        auto &[id, bullet] = *i;
        if (bullet->isDeathTime()){
            bullet->killObject();
            players[id]->addBullet();
            i = bullets.erase(i);
            continue;
        }

        bool wasBreak = false;
        for (auto &player: players) {
            if (!player->isAlive()){
                continue;
            }

            if (player->getGlobalBounds().intersects(bullet->getGlobalBounds())){
                player->killObject();
                bullet->killObject();
                i = bullets.erase(i);
                players[id]->addBullet();
                scores[id].kills++;
                wasBreak = true; break;
            }
        }

        if (!wasBreak){
            i++;
        }
    }

    for (auto &[id, bullet]: bullets) {
        bullet->update(dt);
    }

    int cntLifePlayer = 0, lastLifePlayer = -1;
    for (int i = 0; i < players.size(); ++i){
        if (players[i]->isAlive()){
            cntLifePlayer++;
            lastLifePlayer = i;
        }
        players[i]->update(dt);
    }

    // if (cntLifePlayer == 1){
    //     scores[lastLifePlayer].wins++;
    //     quit = true;
    // }
}

void RoundState::render(std::shared_ptr<sf::RenderTarget> target) {
    if (!target){ target = window; }

    if (map != nullptr) map->render(target);

    for (auto& [id, bullet]: bullets){
        if(bullet != nullptr) bullet->render(*target);
    }

    for (const std::shared_ptr<Player>&  player: players) {
        if (player != nullptr) player->render(*target);
    }

    for (auto &i: scores){
        i.render(*target);
    }
}

void RoundState::initKeybindings() {
    std::ifstream file("../Config/gamestate_keybinds.ini");

    if (file.is_open()){
        std::string action;
        std::string keyBinding;
        while(file >> action >> keyBinding){
            keybindings[action] = supportedKeys[keyBinding];
        }
    }
}

void RoundState::initPlayers() {
    map = std::make_shared<Map>(world, sf::Vector2f(200,50),
                               textures->Box,
                               textures->VerticalBorder,
                               textures->HorizontalBorder);
    players.push_back( std::make_shared<Player>(world, 250, 100, 5, 0, textures->FirstPlayerIdle));
    players.push_back( std::make_shared<Player>(world, 850, 500, 5, 1, textures->SecondPlayerIdle));
    collisionManager = std::make_shared<CollisionManager>(map,players);
}


void RoundState::initTextures() {
    textures = std::make_shared<GameTextures>();
}

void RoundState::initWorld() {
    world = std::make_shared<b2World>(b2Vec2(0, 0));
}

std::vector<std::shared_ptr<Player>> RoundState::getPlayers() {
    return players;
}

std::shared_ptr<Map> RoundState::getMap() {
    return map;
}

std::set<std::pair<int, std::shared_ptr<Bullet>>> RoundState::getBullets() {
    return bullets;
}



Result::Result(float x, float y, const sf::Font &font, const std::string &prefText, int characterSize,
               sf::Color textColor) : textColor(textColor), prefText(prefText) {
    wins = 0;
    kills = 0;
    text.setFont(font);
    text.setString(prefText);
    text.setFillColor(this->textColor);
    text.setCharacterSize(characterSize);
    text.setPosition(x, y);
}

void Result::render(sf::RenderTarget &target) {
    std::string newText = prefText + " " + std::to_string(wins) + "  " + std::to_string(kills);
    text.setString(newText);

    target.draw(text);
}

void RoundState::initFonts() {
    if (!font.loadFromFile("../Fonts/SuperMario256.ttf")){
        std::cout << "Font don't open!\n";
    }
}