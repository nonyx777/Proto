#include "catch.hpp"
#include "../include/Util/Gizmo.hpp"
#include "../include/Entities/Line.hpp"
#include "../include/Entities/Circle.hpp"
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
}