#include "../include/Rigidbody.hpp"


void Rigidbody::euler(sf::Shape *shape)
{
    this->velocity += this->acceleration;
    shape->move(this->velocity);

    this->acceleration = sf::Vector2f(0.f, 0.f);
}

void Rigidbody::verlet(sf::Shape *shape)
{
    current = shape->getPosition();
    this->velocity = (current - previous) + this->acceleration;
    shape->move(this->velocity);
    previous = current;

    this->acceleration = sf::Vector2f(0.f, 0.f);
}