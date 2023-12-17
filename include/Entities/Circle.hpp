#pragma once

#include "../GameObject/GameObject.hpp"

class Circle : public GameObject
{
public:
    sf::CircleShape circle;

public:
    Circle(float radius);

    void update() override;
    void render(sf::RenderTarget *target) override;
};