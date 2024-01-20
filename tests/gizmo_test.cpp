#include "catch.hpp"
#include "../include/Util/Gizmo.hpp"
#include "../include/Entities/Entities.hpp"
#include "../include/Util/Math.hpp"

TEST_CASE("Gizmo Tests")
{
    Gizmo gizmo;
    SECTION("Draw Ray")
    {
        sf::Vector2f start_position = sf::Vector2f(4.f, 4.f);
        sf::Vector2f direction_position = sf::Vector2f(8.f, 8.f);
        float length = 8.f;
        Line line = gizmo.drawRay(start_position, direction_position, length);
        float distance = Math::_length(line.direction - line.base);

        REQUIRE(distance == Approx(length));
    }

    SECTION("Draw Circle")
    {
        sf::Vector2f position = sf::Vector2f(5.f, 5.f);
        float radius = 10.f;
        sf::Color color = sf::Color::White;
        Circle circle = gizmo.drawCircle(position, radius, color);

        REQUIRE(circle.property.getRadius() == Approx(radius));
    }
}