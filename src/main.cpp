#include "../include/Engine/Engine.hpp"

using namespace std;

int main()
{
    Engine engine;

    while(engine.running()){
        engine.update();
        engine.render();
    }

    return 0;
}
