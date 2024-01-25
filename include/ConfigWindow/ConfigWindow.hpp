#pragma once
#include <SFML/Graphics.hpp>
#include "../GameObject/GameObject.hpp"
#include "../../library/UI/imgui.h"
#include "../../library/UI/imgui-SFML.h"
#include "../Globals/globals.hpp"
#include "../Util/Math.hpp"

class ConfigWindow : public GameObject
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

    // ui related
    sf::Clock deltaClock;
    sf::Time deltaTime;

public:
    ConfigWindow();
    ~ConfigWindow();

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