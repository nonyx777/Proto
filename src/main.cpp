#include "../include/Engine/Engine.hpp"
#include "../library/UI/imgui.h"
#include "../library/UI/imgui-SFML.h"

int main()
{
    Engine engine;

    // Create a second SFML window for ImGui rendering
    sf::ContextSettings settings;
    sf::RenderWindow configWindow(sf::VideoMode(200, 200), "Config Window");
    ImGui::SFML::Init(configWindow);

    while (engine.running())
    {
        engine.update();

        // Render ImGui for the second SFML window (outside of the main SFML window)
        configWindow.clear();
        ImGui::SFML::Update(configWindow, sf::seconds(1.f / 60.f));
        ImGui::Begin("Config Window");
        ImGui::Text("Bugsssss");
        ImGui::End();
        ImGui::SFML::Render(configWindow);
        configWindow.display();

        engine.render();
    }

    // Cleanup
    ImGui::SFML::Shutdown();

    return 0;
}
