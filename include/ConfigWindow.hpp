#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include "../library/UI/imgui.h"
#include "../library/UI/imgui-SFML.h"
#include "globals.hpp"
#include "./Util/Math.hpp"
#include "Window.hpp"

class ConfigWindow : public Window
{
public:
    // initializer functions
    void initWindow() override;

public:
    void update() override;
    void render(sf::RenderTarget *target) override;
};