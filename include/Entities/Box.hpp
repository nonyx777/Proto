#pragma once

#include "../GameObject.hpp"
#include "../Rigidbody.hpp"
#include "Entity.hpp"

class Box : public GameObject, public Rigidbody, public Entity
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

    void calcMomentOfInertia() override;
    void update() override;
    void render(sf::RenderTarget *target) override;
};