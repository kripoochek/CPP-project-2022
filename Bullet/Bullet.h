/*#ifndef GAME_BULLET_H
#define GAME_BULLET_H

#include "cmath"
#include <utility>
#include "Entity.h"

namespace Bullet {
    struct Bullet : DynamicObject {
    private:
        int lifeTime = 4000;
        float moveSpeed = 0.1f;
        sf::Sprite sprite;
        sf::Texture texture;
        float direction;
    public:
        Bullet(const float& direction,const float& x,const float& y,const int& lifetime);
        Bullet();
        int getLifeTime();


        void setLifeTime(int newLifeTime);

        void draw(sf::RenderWindow *window) override;
        void checkCollision() const;
        void updatePositions();

        void setTexture(const std::string &file) override;
        void setDirection(float newDirection);
        void setStartPosition(const float& x,const float& y);
    };
}
#endif //GAME_BULLET_H
*/