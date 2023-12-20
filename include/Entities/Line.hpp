#pragma once

#include "../GameObject/GameObject.hpp"

class Line : public GameObject
{
public:
    sf::Vector2f base;
    sf::Vector2f direction;

    Line(sf::Vector2f base, sf::Vector2f direction);

    void update() override;
    void render(sf::RenderTarget *target) override;
};