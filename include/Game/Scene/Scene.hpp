#pragma once

#include "../../GameObject/GameObject.hpp"
#include "../../Entities/Entities.hpp"
#include "../../Util/Gizmo.hpp"

class Scene : public GameObject
{
private:
    static Scene *instance;
    Gizmo gizmo;

private:
    Scene();
    ~Scene();

public:
    // Delete copy constructor and assignment operator to prevent cloning
    Scene(const Scene &) = delete;
    Scene &operator=(const Scene &) = delete;

    static Scene *getInstance();

    void update() override;
    void render(sf::RenderTarget *target) override;
};