#ifndef GAME_BULLET_H
#define GAME_BULLET_H
#include "../constants.h"
#include "cmath"
#include <utility>
#include "DynamicObject.h"
namespace Bullet {
    struct Bullet{
    private:
        int lifeTime=5;
        float moveSpeed = 0.1f;
        sf::Sprite sprite;
        sf::Texture texture;
        float direction;
    public:
        Bullet()=default;
        virtual ~Bullet()=default;
        virtual int getLifeTime();
        virtual void setDirection(float newDirection);
        virtual void setLifeTime(int newLifeTime);
        virtual void setMoveSpeed(float newMoveSpeed);
        virtual void draw(sf::RenderWindow* window);
        virtual void updatePositions();
        virtual void setTexture(const std::string &file);
        //virtual void updateDirection();
        [[nodiscard]] const sf::Vector2f& getPosition() const;
    };
}
#endif //GAME_BULLET_H
