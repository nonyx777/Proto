#pragma once

#include "../GameObject/GameObject.hpp"

class Box : public GameObject
{
    public:
        sf::RectangleShape property;
    private:
        void initVariables();
    public:
        Box();

        void update() override;
        void render(sf::RenderTarget* target) override;
};