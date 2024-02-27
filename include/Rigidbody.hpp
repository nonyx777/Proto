#pragma once
#include <SFML/Graphics.hpp>

class Rigidbody
{
public:
    sf::Vector2f linearVelocity;
    sf::Vector2f linearAcceleration;
    float angularVelocity;
    float angularAcceleration;
    float elasticity;

    void euler(sf::Shape *shape);
    void verlet(sf::Shape *shape);

    // verlet related
    sf::Vector2f current, previous;
};