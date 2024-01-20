#pragma once

#include "../GameObject/GameObject.hpp"
#include "../Entity/Entity.hpp"

class Line : public GameObject, public Entity
{
public:
    sf::Vector2f base;
    sf::Vector2f direction;

    Line();
    Line(sf::Vector2f base, sf::Vector2f direction);

    void integrate() override;

    void update() override;
    void render(sf::RenderTarget *target) override;
};