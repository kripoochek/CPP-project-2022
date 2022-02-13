#include "Controller.h"
Controller::Controller() {
    objects.push_back(new Tank);
    objects.push_back(new Tank);
    sf::Texture t;
    objects[0]->setTexture("../sprites/tank0.png");
    objects[1]->setTexture("../sprites/tank1.png");
}
std::vector<DynamicObject*> Controller::getObjects(){
    return objects;
}
void Controller::tankMovement() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        objects[0]->updateRotate(false);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        objects[0]->updateRotate(true);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        objects[0]->updatePositions(false);
    }
    else if (sf::Keyboard::isKeyPressed((sf::Keyboard::S))){
        objects[0]->updatePositions(true);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)){
        objects[1]->updateRotate(false);
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
        objects[1]->updateRotate(true);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
        objects[1]->updatePositions(false);
    }
    else if (sf::Keyboard::isKeyPressed((sf::Keyboard::Down))){
        objects[1]->updatePositions(true);
    }
}

