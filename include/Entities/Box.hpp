#pragma once

#include "../GameObject/GameObject.hpp"
#include "../Entity/Entity.hpp"

class Box : public GameObject, public Entity
{
public:
    sf::RectangleShape property;

private:
    void initVariables();

public:
    Box();

    void update() override;
    void render(sf::RenderTarget *target) override;
};