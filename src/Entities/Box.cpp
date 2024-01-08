#include "../../include/Entities/Box.hpp"

Box::Box()
{
}

void Box::initVariables()
{
    this->inverseMass = this->mass == 0.f ? 100000.f : 1.f / this->mass;
    this->property.setFillColor(sf::Color::White);
    this->property.setOrigin(this->property.getSize()/2.f);
}

void Box::update()
{
    //...
}

void Box::render(sf::RenderTarget *target)
{
    target->draw(this->property);
}