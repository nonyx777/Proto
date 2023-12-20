#include "../../include/Entities/Box.hpp"

Box::Box()
{
    this->inverseMass = this->mass == 0.f ? 100000.f : 1.f / this->mass;
}

void Box::update()
{
    //...
}

void Box::render(sf::RenderTarget *target)
{
    target->draw(this->box);
}