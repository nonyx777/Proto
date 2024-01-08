#pragma once

#include "../GameObject/GameObject.hpp"

class Box : public GameObject
{
    public:
        sf::RectangleShape box;
    private:
        void initVariables();
    public:
        Box();

        void update() override;
        void render(sf::RenderTarget* target) override;
};