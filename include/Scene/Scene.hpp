#pragma once

#include "../GameObject/GameObject.hpp"
#include "../Entities/Entities.hpp"

class Scene : public GameObject
{
public:
    Scene();

    void update() override;
    void render(sf::RenderTarget *target) override;
};