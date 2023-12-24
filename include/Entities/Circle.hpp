#pragma once

#include "../GameObject/GameObject.hpp"

class Circle : public GameObject
{
public:
    sf::CircleShape circle;

private:
    void initVariables();

public:
    Circle();
    Circle(float radius);

    void update() override;
    void render(sf::RenderTarget *target) override;
};