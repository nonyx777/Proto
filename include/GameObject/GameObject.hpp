#pragma once
#include <SFML/Graphics.hpp>

class GameObject
{
public:
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    float mass;
    float inverseMass;
    float elasticity;

public:
    virtual void update() = 0;
    virtual void render(sf::RenderTarget* target) = 0;
};