#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../GameObject/GameObject.hpp"
#include "../Game/Scene/Scene.hpp"
#include "../../library/UI/imgui.h"
#include "../../library/UI/imgui-SFML.h"

using namespace std;

class Engine : public GameObject
{
private:
    // initializer functions
    void initVariables();
    void initWindow();

public:
    // window variables
    sf::RenderWindow *window;

private:
    sf::VideoMode video_mode;
    sf::Event event;

    // mouse position
    sf::Vector2i mouse_position;
    sf::Vector2f mouse_position_view;

    // ui related
    sf::Clock deltaClock;
    sf::Time deltaTime;

private:
    Scene *scene = Scene::getInstance();

public:
    Engine();
    ~Engine();

    void pollEvent();
    void update() override;
    void render(sf::RenderTarget *target) override;
    void render();

    const bool running() const;

    // ui related
    void initImGui();
    void eventImGui();
    void updateImGui();
    void renderImGui();
};
