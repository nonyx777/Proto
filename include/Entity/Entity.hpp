#pragma once
#include <SFML/Graphics.hpp>

class Entity
{
public:
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    float mass;
    float inverseMass;
    float elasticity;

public:
    virtual void integrate();
};