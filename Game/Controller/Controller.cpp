#include "Controller.h"

Controller::Controller() {
    tanks.push_back(new Tank);
    tanks.push_back(new Tank);
    bullets.push_back(new Bullet::Bullet);
    sf::Texture t;
    tanks[0]->setTexture("../sprites/tank0.png");
    tanks[1]->setTexture("../sprites/tank1.png");
    bullets[0]->setTexture("../sprites/bullet0.png");
    bullets[0]->setDirection(0.5);
}

std::vector<DynamicObject*> Controller::getTanks(){
    return tanks;
}

std::vector<Bullet::Bullet*> Controller::getBullets() {
    return bullets;
}

void Controller::tankMovement() {
    if (bullets[0]->getLifeTime()>=0) {
        bullets[0]->updatePositions();
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        tanks[0]->updateRotate(false);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        tanks[0]->updateRotate(true);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        tanks[0]->updatePositions(false);
    }
    else if (sf::Keyboard::isKeyPressed((sf::Keyboard::S))){
        tanks[0]->updatePositions(true);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        tanks[1]->updateRotate(false);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        tanks[1]->updateRotate(true);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        tanks[1]->updatePositions(false);
    }
    else if (sf::Keyboard::isKeyPressed((sf::Keyboard::Down))){
        tanks[1]->updatePositions(true);
    }
}

