
#ifndef MY_TANKS_IN_LABIRINT_WALL_H
#define MY_TANKS_IN_LABIRINT_WALL_H



#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
class Wall {
private:
    sf::Sprite sprite;
public:
    bool hidden=false;
    Wall(sf::Vector2f coordinates,const sf::Texture& texture_);
    void setTexture(const sf::Texture& texture_);
    void setPosition(sf::Vector2f coordinates);
    void render(std::shared_ptr<sf::RenderTarget> target);

};


#endif //MY_TANKS_IN_LABIRINT_WALL_H
