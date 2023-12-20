#include "../../include/Entities/Circle.hpp"

Circle::Circle(float radius)
{
    this->circle.setRadius(radius);
    this->circle.setFillColor(sf::Color::White);
    this->inverseMass = this->mass == 0.f ? 100000.f : 1.f / this->mass;
}

void Circle::update()
{
    //....
}

void Circle::render(sf::RenderTarget *target)
{
    target->draw(this->circle);
}