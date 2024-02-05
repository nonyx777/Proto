#pragma once
#include <SFML/Graphics.hpp>

namespace Rigidbody
{
    struct RigidbodyAttr
    {
        sf::Vector2f velocity;
        sf::Vector2f acceleration;
        float mass;
        float inverseMass;
        float elasticity;
    };

    namespace Euler
    {
        void integrate(sf::Shape *shape);
    }

    namespace Verlet
    {
        void integrate(sf::Shape *shape);
    }
}