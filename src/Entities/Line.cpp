#include "../../include/Entities/Line.hpp"

Line::Line()
{
    //...
}

Line::Line(sf::Vector2f base, sf::Vector2f direction)
{
    this->base = base;
    this->direction = direction;
}

void Line::update()
{
    //...
}

void Line::render(sf::RenderTarget *target)
{
    sf::Vertex line[] = {
        this->base,
        this->direction};
    target->draw(line, 2, sf::Lines);
}