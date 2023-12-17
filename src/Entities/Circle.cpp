#include "../../include/Entities/Circle.hpp"

Circle::Circle(float radius)
{
    this->circle.setRadius(radius);
    this->circle.setFillColor(sf::Color::White);
}

void Circle::update()
{
    //....
}

void Circle::render(sf::RenderTarget *target)
{
    target->draw(this->circle);
}