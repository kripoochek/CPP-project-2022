#include "GameMap.h"
#include "Controller.h"
int main()
{
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(1024, 768), "SFML works!");
    GameMap map(window);
    Controller tanksControl;
    while (window->isOpen())
    {
        sf::Event event;
        while (window->pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window->close();

        }
        tanksControl.tankMovement();
        window->clear();
        window->draw(map.getSprite());
        for (auto i: tanksControl.getObjects()){ i->draw(window); }
        window->display();
    }
    delete window;
    return 0;
}