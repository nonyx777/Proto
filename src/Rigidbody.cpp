#include "../include/Rigidbody.hpp"


void Rigidbody::euler(sf::Shape *shape)
{
    this->linearVelocity += this->linearAcceleration;
    shape->move(this->linearVelocity);

    this->linearAcceleration = sf::Vector2f(0.f, 0.f);
}

void Rigidbody::verlet(sf::Shape *shape)
{
    current = shape->getPosition();
    this->linearVelocity = (current - previous) + this->linearAcceleration;
    shape->move(this->linearVelocity);
    previous = current;

    this->linearAcceleration = sf::Vector2f(0.f, 0.f);
}