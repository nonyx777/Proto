#include "../../include/Entity/Entity.hpp"

void Entity::integrate(sf::Shape *shape)
{
    this->velocity += this->acceleration;
    shape->move(this->velocity);

    this->acceleration = sf::Vector2f(0.f, 0.f);
    this->velocity = sf::Vector2f(0.f, 0.f);
}