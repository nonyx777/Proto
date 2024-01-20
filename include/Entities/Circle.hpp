#pragma once

#include "../GameObject/GameObject.hpp"
#include "../Entity/Entity.hpp"

class Circle : public GameObject, public Entity
{
public:
    sf::CircleShape property;

private:
    void initVariables();

public:
    Circle();
    Circle(float radius);

    void update() override;
    void render(sf::RenderTarget *target) override;
};