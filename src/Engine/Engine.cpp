#include "../../include/Engine/Engine.hpp"

// defining initializer functions
void Engine::initVariables()
{
    this->window = nullptr;
}
void Engine::initWindow()
{
    this->video_mode.width = 600;
    this->video_mode.height = 600;
    this->window = new sf::RenderWindow(this->video_mode, "Window", sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

Engine::Engine()
{
    this->initVariables();
    this->initWindow();
}
Engine::~Engine()
{
    delete this->window;
}

const bool Engine::running() const
{
    return this->window->isOpen();
}

void Engine::pollEvent()
{
    while (this->window->pollEvent(this->event))
    {
        switch (this->event.type)
        {
        case sf::Event::Closed:
            this->window->close();
            break;
        }
    }
}
void Engine::update()
{
    this->pollEvent();
    this->mouse_position = sf::Mouse::getPosition(*this->window);
    this->mouse_position_view = this->window->mapPixelToCoords(this->mouse_position);

    scene->update();
}
void Engine::render(sf::RenderTarget *target)
{
    //....
}
void Engine::render()
{
    this->window->clear(sf::Color::Black);
    scene->render(this->window);
    this->window->display();
}
