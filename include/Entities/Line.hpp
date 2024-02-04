#pragma once

#include "../GameObject.hpp"
#include "../Rigidbody.hpp"

class Line : public GameObject, public Rigidbody
{
public:
    sf::Vector2f base;
    sf::Vector2f direction;

    Line();
    Line(sf::Vector2f base, sf::Vector2f direction);

    void update() override;
    void render(sf::RenderTarget *target) override;
};