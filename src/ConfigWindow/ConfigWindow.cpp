#include "../../include/ConfigWindow/ConfigWindow.hpp"

void ConfigWindow::initVariables()
{
    this->window = nullptr;
}
void ConfigWindow::initWindow()
{
    this->video_mode.width = 200;
    this->video_mode.height = 400;
    this->window = new sf::RenderWindow(this->video_mode, "Configuration Window", sf::Style::Titlebar | sf::Style::Close);
    this->window->setFramerateLimit(60);
}

ConfigWindow::ConfigWindow()
{
    this->initVariables();
    this->initWindow();
    this->initImGui();
}
ConfigWindow::~ConfigWindow()
{
    ImGui::SFML::Shutdown();
    delete this->window;
}

const bool ConfigWindow::running() const
{
    return this->window->isOpen();
}

void ConfigWindow::pollEvent()
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

void ConfigWindow::update()
{
    this->pollEvent();

    this->updateImGui();
    ImGui::Begin("Paramters");
    ImGui::InputInt("Window Height ", &GLOBAL::window_height);
    ImGui::InputInt("Window Width ", &GLOBAL::window_width);
    ImGui::End();
}

void ConfigWindow::render(sf::RenderTarget *target)
{
    //....
}
void ConfigWindow::render()
{
    this->window->clear(sf::Color::Black);
    this->renderImGui();
    this->window->display();
}

void ConfigWindow::initImGui()
{
    ImGui::SFML::Init(*window, true);
}
void ConfigWindow::eventImGui()
{
    ImGui::SFML::ProcessEvent(this->event);
}
void ConfigWindow::updateImGui()
{
    ImGui::SFML::Update(*window, this->deltaClock.restart());
}
void ConfigWindow::renderImGui()
{
    ImGui::SFML::Render(*window);
}