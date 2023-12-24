#include "../GameObject/GameObject.hpp"
#include "../../include/Entities/Entities.hpp"
#include "../../include/Util/Math.hpp"

class Gizmo
{
private:
    Line line;
    Circle circle;

public:
    Gizmo();

public:
    Line drawRay(sf::Vector2f start_position, sf::Vector2f direction, float length);
    Circle drawSphere(sf::Vector2f position, float radius, sf::Color color);
};