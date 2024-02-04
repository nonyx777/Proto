#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameObject.hpp"
#include "./Game/Scene.hpp"
#include "../library/UI/imgui.h"
#include "../library/UI/imgui-SFML.h"
#include "globals.hpp"
#include "Window.hpp"

using namespace std;

class Engine : public Window
{
public:
    // initializer functions
    void initWindow() override;

public:
    Engine();

    void update() override;
    void render(sf::RenderTarget *target) override;
    void render();

private:
    Scene *scene = Scene::getInstance();
};
