#pragma once

#include "../GameObject.hpp"
#include "../Rigidbody.hpp"

class Circle : public GameObject, public Rigidbody::RigidbodyAttr
{
public:
    sf::CircleShape property;

private:
    void initVariables();

public:
    Circle();
    Circle(float radius);

    void update() override;
    void render(sf::RenderTarget *target) override;
};