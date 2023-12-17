#pragma once
#include <SFML/Graphics.hpp>

class GameObject
{
protected:
    sf::Vector2f velocity;
    sf::Vector2f acceleration;
    sf::Vector2f mass;

public:
    virtual void update() = 0;
    virtual void render(sf::RenderTarget* target) = 0;
};