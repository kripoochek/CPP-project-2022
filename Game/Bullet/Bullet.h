#ifndef GAME_BULLET_H
#define GAME_BULLET_H

#include "../constants.h"
#include "cmath"
#include <utility>
#include "DynamicObject.h"

namespace Bullet {
    struct Bullet : DynamicObject {
    private:
        int lifeTime = 4000;
        float moveSpeed = 0.1f;
        sf::Sprite sprite;
        sf::Texture texture;
        float direction;
    public:
        Bullet() = default;

        int getLifeTime();

        void setDirection(float newDirection);

        void setLifeTime(int newLifeTime);

        void setMoveSpeed(float newMoveSpeed);

        void draw(sf::RenderWindow *window);

        void updatePositions();

        void setTexture(const std::string &file);

        //virtual void updateDirection();
        [[nodiscard]] const sf::Vector2f &getPosition() const;
    };
}
#endif //GAME_BULLET_H
