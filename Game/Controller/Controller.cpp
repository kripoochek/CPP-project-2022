#include "Controller.h"

Controller::Controller() {
    tanks.push_back(new Tank(100, 100, "../sprites/tank0.png"));
    tanks.push_back(new Tank(0, 0, "../sprites/tank1.png"));

    bullets.push_back(new Bullet::Bullet);
    bullets[0]->setTexture("../sprites/bullet0.png");
    bullets[0]->setDirection(0.5);
}

std::vector<Tank*> Controller::getTanks(){
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
        if (tanks[0]->intersects(*tanks[1])){
            tanks[0]->updateRotate(true);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        tanks[0]->updateRotate(true);
        if (tanks[0]->intersects(*tanks[1])){
            tanks[0]->updateRotate(false);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        tanks[0]->updatePositions(false);
        if (tanks[0]->intersects(*tanks[1])){
            tanks[0]->updatePositions(true);
        }
    }
    else if (sf::Keyboard::isKeyPressed((sf::Keyboard::S))){
        tanks[0]->updatePositions(true);
        if (tanks[0]->intersects(*tanks[1])){
            tanks[0]->updatePositions(false);
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        tanks[1]->updateRotate(false);
        if (tanks[0]->intersects(*tanks[1])){
            tanks[1]->updateRotate(true);
        }
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        tanks[1]->updateRotate(true);
        if (tanks[0]->intersects(*tanks[1])){
            tanks[1]->updateRotate(false);
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        tanks[1]->updatePositions(false);
        if (tanks[0]->intersects(*tanks[1])){
            tanks[1]->updatePositions(true);
        }
    }
    else if (sf::Keyboard::isKeyPressed((sf::Keyboard::Down))){
        tanks[1]->updatePositions(true);
        if (tanks[0]->intersects(*tanks[1])){
            tanks[1]->updatePositions(false);
        }
    }
}

