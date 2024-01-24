#include "../include/Engine/Engine.hpp"
#include "../library/UI/imgui.h"
#include "../library/UI/imgui-SFML.h"

bool tempo = false;
sf::Event event;

int main()
{

    // Create a second SFML window for ImGui rendering
    sf::ContextSettings settings;
    sf::RenderWindow configWindow(sf::VideoMode(200, 200), "Config Window");
    configWindow.setFramerateLimit(60);
    ImGui::SFML::Init(configWindow);

    while (!tempo)
    {
        while (configWindow.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(event);
            switch (event.type)
            {
                case sf::Event::Closed:
                    tempo = true;
                    configWindow.close();
                    break;
            }
        }

        // Render ImGui for the second SFML window (outside of the main SFML window)
        configWindow.clear();
        ImGui::SFML::Update(configWindow, sf::seconds(1.f / 60.f));
        ImGui::Begin("Config Window");
        ImGui::Text("Bugsssss");
        ImGui::End();
        ImGui::SFML::Render(configWindow);
        configWindow.display();
    }

    Engine engine;
    if (tempo == true)
    {
        while (engine.running())
        {
            engine.update();
            engine.render();
        }
    }

    // Cleanup
    ImGui::SFML::Shutdown();

    return 0;
}
