
#ifndef MY_TANKS_IN_LABIRINT_WALL_H
#define MY_TANKS_IN_LABIRINT_WALL_H



#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include <memory>
enum class Type{
    horizontal=0,
    vertical=1
};
class Wall {
private:
    sf::Sprite sprite;
    Type type;
public:
    Wall(sf::Vector2f coordinates,const sf::Texture& texture_,bool type);
    void setTexture(const sf::Texture& texture_);
    void setPosition(sf::Vector2f coordinates);
    void render(std::shared_ptr<sf::RenderTarget> target);
    Type getType();
};


#endif //MY_TANKS_IN_LABIRINT_WALL_H
