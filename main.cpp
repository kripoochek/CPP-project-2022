//
// Created by andrey on 05.02.2022.
//
#include "main.h"
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>

int main() {
    sf::RenderWindow window(sf::VideoMode(640, 480), "GameWindow", sf::Style::Titlebar | sf::Style::Close);
    sf::Event ev;

    while (window.isOpen()) {
        while (window.pollEvent(ev)){
            switch (ev.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::KeyPressed:{
                    if (ev.key.code==sf::Keyboard::Escape){
                        window.close();
                    }
                    break;
                }

            }
        }
        window.clear();
        window.display();

    }

    return 0;
}