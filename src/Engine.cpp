#include "../include/Engine.hpp"

// defining initializer functions
void Engine::initVariables()
{
    this->window = nullptr;
}
void Engine::initWindow()
{
    this->video_mode.width = GLOBAL::window_width;
    this->video_mode.height = GLOBAL::window_height;
    this->window = new sf::RenderWindow(this->video_mode, "Proto", sf::Style::Titlebar | sf::Style::Resize | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

Engine::Engine()
{
    this->initVariables();
    this->initWindow();
    this->initImGui();
}
Engine::~Engine()
{
    ImGui::SFML::Shutdown();
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
        this->eventImGui();
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
    this->updateImGui();
    ImGui::Begin("Proto");
    ImGui::Text("Tools incoming!");
    ImGui::End();
}
void Engine::render(sf::RenderTarget *target)
{
    //....
}
void Engine::render()
{
    this->window->clear(sf::Color::Black);
    scene->render(this->window);
    this->renderImGui();
    this->window->display();
}

void Engine::initImGui()
{
    ImGui::SFML::Init(*window, true);
}
void Engine::eventImGui()
{
    ImGui::SFML::ProcessEvent(this->event);
}
void Engine::updateImGui()
{
    ImGui::SFML::Update(*window, this->deltaClock.restart());
}
void Engine::renderImGui()
{
    ImGui::SFML::Render(*window);
}