#pragma once

#include "../GameObject.hpp"
#include "../Rigidbody.hpp"

class Box : public GameObject, public Rigidbody
{
public:
    sf::RectangleShape property;
    uint row, col;

private:
    void initVariables();

public:
    Box();
    Box(uint size);
    Box(uint size, sf::Vector2f position);

    void update() override;
    void render(sf::RenderTarget *target) override;
};