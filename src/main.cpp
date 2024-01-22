#include "../include/Engine/Engine.hpp"
#include "../library/UI/imgui.h"
#include "../library/UI/imgui-SFML.h"

using namespace std;

int main()
{
    Engine engine;

    while (engine.running())
    {
        engine.update();
        engine.render();
    }

    ImGui::SFML::Shutdown();
    return 0;
}
