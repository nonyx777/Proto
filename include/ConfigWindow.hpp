#pragma once
#include <SFML/Graphics.hpp>
#include "./Util/Math.hpp"
#include "Window.hpp"

class ConfigWindow : public Window
{
public:
    // initializer functions
    void initWindow() override;

public:
    ConfigWindow();

    void update() override;
    void render(sf::RenderTarget *target) override;
};