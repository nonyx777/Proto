#include "../include/Engine/Engine.hpp"
#include "../include/ConfigWindow/ConfigWindow.hpp"
#include "../library/UI/imgui.h"
#include "../library/UI/imgui-SFML.h"

sf::Event event;

int main()
{
    // Create a second SFML window for ImGui rendering
    ConfigWindow configWindow;
    while (configWindow.running())
    {
        configWindow.update();
        configWindow.render();
    }

    Engine engine;
    while (engine.running())
    {
        engine.update();
        engine.render();
    }

    return 0;
}
