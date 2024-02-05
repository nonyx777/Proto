#include "../include/Rigidbody.hpp"

Rigidbody::RigidbodyAttr rbAttr;

void Rigidbody::Euler::integrate(sf::Shape *shape)
{
    rbAttr.velocity += rbAttr.acceleration;
    shape->move(rbAttr.velocity);

    rbAttr.acceleration = sf::Vector2f(0.f, 0.f);
    rbAttr.velocity = sf::Vector2f(0.f, 0.f);
}

void Rigidbody::Verlet::integrate(sf::Shape *shape)
{
    //Todo
}