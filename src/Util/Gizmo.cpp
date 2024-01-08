#include "../../include/Util/Gizmo.hpp"

Gizmo::Gizmo()
{
}

Line Gizmo::drawRay(sf::Vector2f start_position, sf::Vector2f direction, float length)
{
    this->line.base = start_position;

    sf::Vector2f dir_norm = Math::_normalize(direction);
    dir_norm *= length;

    direction = start_position + dir_norm;

    this->line.direction = direction;

    return this->line;
}

Circle Gizmo::drawSphere(sf::Vector2f position, float radius, sf::Color color)
{
    this->circle.property.setRadius(radius);
    this->circle.property.setPosition(position);
    this->circle.property.setFillColor(color);
    return this->circle;
}