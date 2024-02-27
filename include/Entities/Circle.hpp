#pragma once

#include "../GameObject.hpp"
#include "../Rigidbody.hpp"
#include "Entity.hpp"

class Circle : public GameObject, public Rigidbody, public Entity
{
public:
    sf::CircleShape property;

private:
    void initVariables();

public:
    Circle();
    Circle(float radius);

    void calcMomentOfInertia() override;
    void update() override;
    void render(sf::RenderTarget *target) override;
};