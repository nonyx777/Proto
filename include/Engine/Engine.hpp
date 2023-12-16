#pragma once
#include <iostream>
#include <SFML/Graphics.hpp>

using namespace std;

class Engine{
    private:
        //initializer functions
        void initVariables();
        void initWindow();

        //window variables
        sf::RenderWindow* window;
        sf::VideoMode video_mode;
        sf::Event event;

        //mouse position
        sf::Vector2i mouse_position;
        sf::Vector2f mouse_position_view;

    public:
        Engine();
        ~Engine();

        void pollEvent();
        void update();
        void render();

        const bool running() const;
};
