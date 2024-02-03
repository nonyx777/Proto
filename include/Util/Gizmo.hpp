#include "../GameObject.hpp"
#include "../Entities/Entities.hpp"
#include "Math.hpp"

class Gizmo
{
private:
    Line line;
    Circle circle;

public:
    Gizmo();

public:
    Line drawRay(sf::Vector2f start_position, sf::Vector2f direction, float length);
    Circle drawCircle(sf::Vector2f position, float radius, sf::Color color);
};