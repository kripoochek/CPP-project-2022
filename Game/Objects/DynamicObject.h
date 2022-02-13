#ifndef TANKS_IN_LABIRINT_DYNAMICOBJECT_H
#define TANKS_IN_LABIRINT_DYNAMICOBJECT_H

#include <SFML/Graphics.hpp>
#include <string>
#include<cmath>

struct DynamicObject {
    DynamicObject() = default;
    virtual ~DynamicObject() = default;

    [[nodiscard]] const sf::Vector2f& getPosition() const;
    [[nodiscard]] float getRotate() const;

    virtual void setRotate(float newRotate);
    virtual void setMoveSpeed(float newMoveSpeed);
    virtual void setRotateSpeed(float newRotateSpeed);
    virtual void setTexture(const std::string &file);

    virtual void updateRotate(bool clockwise);
    virtual void updatePositions(bool back);

    virtual void draw(sf::RenderWindow* window);
private:
    float moveSpeed = 0.1f, rotateSpeed = 0.1f;
    sf::Sprite sprite;
    sf::Texture texture;
};

#endif //TANKS_IN_LABIRINT_DYNAMICOBJECT_H
