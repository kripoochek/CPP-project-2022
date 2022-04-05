#ifndef MY_TANKS_IN_LABIRINT_ENTITY_H
#define MY_TANKS_IN_LABIRINT_ENTITY_H

#include "MovementComponent.h"
#include "HitboxComponent.h"

struct Entity {
    //Constructors/Destructors
    Entity();

    //Getters
    sf::FloatRect getGlobalBounds() const;

    //Component functions
    void setTexture(sf::Texture &texture);
    void createMovementComponent(float maxVelocityMove, float maxVelocityRotate, float currentVelocityMove, float acceleration, float deceleration);
    void createHitboxComponent(sf::Sprite &sprite, float offsetX, float offsetY, float width, float height);

    //Functions
    virtual void setPosition(float x, float y);
    virtual void move(bool forward, float dt);
    virtual void rotate(bool clockwise, float dt);
    virtual void update(float dt);
    virtual void render(sf::RenderTarget& target);
    std::shared_ptr<HitboxComponent> hitboxComponent;
protected:
    std::shared_ptr<MovementComponent> movementComponent;
    sf::Sprite sprite;
private:
    void initVariables();
};


#endif //MY_TANKS_IN_LABIRINT_ENTITY_H
