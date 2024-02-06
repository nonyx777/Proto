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

    void euler(sf::Shape *shape);
    void verlet(sf::Shape *shape);

    // verlet related
    sf::Vector2f current, previous;
};