#include "Controller.h"
int main()
{
    std::vector<DynamicObject*> objects;
    objects.push_back(new Tank);
    objects.push_back(new Tank);
    sf::Texture t;
    objects[0]->setTexture("../sprites/tank0.png");
    objects[1]->setTexture("../sprites/tank1.png");
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1024, 768), "SFML works!");
    Map gameMap;
    sf::RenderTexture mapTex;
    Theme* theme = new SimpleTheme();
    mapTex.create(window->getSize().x, window->getSize().y);

    gameMap.setTheme(theme);
    gameMap.generate();
    gameMap.draw(mapTex);
    sf::Sprite gameMapView(mapTex.getTexture());

    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();
        }
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
        window->clear();
        window->draw(gameMapView);
        for (auto i: objects){ i->draw(window); }
        window->display();
    }
    return 0;
}