#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../GameObject/GameObject.hpp"

using namespace std;

class Engine : public GameObject
{
private:
    // initializer functions
    void initVariables();
    void initWindow();

    // window variables
    sf::RenderWindow *window;
    sf::VideoMode video_mode;
    sf::Event event;

    // mouse position
    sf::Vector2i mouse_position;
    sf::Vector2f mouse_position_view;

public:
    Engine();
    ~Engine();

    void pollEvent();
    void update() override;
    void render() override;

    const bool running() const;
};
