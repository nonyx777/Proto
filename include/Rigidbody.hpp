#pragma once
#include <SFML/Graphics.hpp>

class Rigidbody
{
public:
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    float mass;
    float inverseMass;
    float elasticity;

public:
    void integrate(sf::Shape* shape);
};