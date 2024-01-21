#pragma once

#include "../GameObject/GameObject.hpp"
#include "../Entity/Entity.hpp"

class Box : public GameObject, public Entity
{
public:
    sf::RectangleShape property;
    uint row, col;

private:
    void initVariables();

public:
    Box();
    Box(uint size, sf::Vector2f position);

    void update() override;
    void render(sf::RenderTarget *target) override;
};