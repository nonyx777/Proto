#include "../../../include/Game/Scene/Scene.hpp"

Scene *Scene::instance = nullptr;

Scene::Scene()
{
    //....
}

Scene::~Scene()
{
    delete instance;
}

Scene *Scene::getInstance()
{
    if (!instance)
        instance = new Scene();

    return instance;
}

void Scene::update()
{
    //....
}

void Scene::render(sf::RenderTarget *target)
{
    //....
}