#include "../../include/ConfigWindow/ConfigWindow.hpp"

void ConfigWindow::initVariables()
{
    this->window = nullptr;
}
void ConfigWindow::initWindow()
{
    this->video_mode.width = GLOBAL::config_window_width;
    this->video_mode.height = GLOBAL::config_window_height;
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
    ImGui::Begin("Parameters", nullptr, ImGuiWindowFlags_NoMove);
    ImGui::SetWindowSize(ImVec2(this->window->getSize()));

    //configure engine window size
    ImGui::Text("Window Size");
    ImGui::InputInt("Window Height", &GLOBAL::window_height);
    ImGui::InputInt("Window Width", &GLOBAL::window_width);

    GLOBAL::window_height = Math::_clampOnRange(GLOBAL::window_height, 400, 1000);
    GLOBAL::window_width = Math::_clampOnRange(GLOBAL::window_width, 400, 1000);

    //Todo: configure grid
    ImGui::Text("Grid Configuration");
    ImGui::InputInt("Cell Size", &GLOBAL::cell_size);
    if(ImGui::Button("Display Grid"))
        GLOBAL::display_grid = !GLOBAL::display_grid;
    ImGui::Text("Display Grid: %s", GLOBAL::display_grid ? "True" : "False");

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