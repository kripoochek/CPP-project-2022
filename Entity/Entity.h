#ifndef MY_TANKS_IN_LABIRINT_ENTITY_H
#define MY_TANKS_IN_LABIRINT_ENTITY_H

#include "MovementComponent.h"
#include "HitboxComponent.h"

struct Entity {
    //Constructors/Destructors
    Entity();

    //Component functions
    virtual void setTexture(sf::Texture &texture);
    virtual void createMovementComponent(float maxVelocityMove, float maxVelocityRotate, float currentVelocityMove, float acceleration, float deceleration);
    virtual void createHitboxComponent(sf::Sprite &sprite, float offsetX, float offsetY, float width, float height);

    //Setters
    virtual void setPosition(float x, float y);
    virtual void setPosition(sf::Vector2f& coordinates);
    virtual void setOrigin(float x, float y);
    virtual void setRotation(float newRotation);

    //Getters
    virtual const sf::Vector2f& getPosition() const;
    virtual const sf::Vector2f& getSpritePosition() const;
    virtual sf::FloatRect getGlobalBounds() const;
    virtual sf::FloatRect getNextPositionBounds(float dt) const;
    virtual float getRotation();


    virtual void rotate(bool clockwise, float dt);
    virtual void move(bool forward, float dt);
    virtual void stopVelocity();
    virtual void stopVelocityX();
    virtual void stopVelocityY();

    virtual void update(float dt);
    virtual void render(sf::RenderTarget& target);
protected:
    std::shared_ptr<MovementComponent> movementComponent;
    std::shared_ptr<HitboxComponent> hitboxComponent;
    sf::Sprite sprite;
private:
    void initVariables();
};


#endif //MY_TANKS_IN_LABIRINT_ENTITY_H
