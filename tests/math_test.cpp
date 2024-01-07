#include "catch.hpp"
#include "../include/Util/Math.hpp"

TEST_CASE("Math Tests")
{
    SECTION("Trig Operations")
    {
        REQUIRE(round(Math::_sin(90.f)) == 1.f);
        REQUIRE(round(Math::_cos(90.f)) == 0.f);
    }

    SECTION("Angle Conversion")
    {
        float degree = 90.f;
        float radian = 1.5708f;

        float expected_deg = round(radian * Math::_rad2Deg());
        float expected_rad = degree * Math::_deg2Rad();
        
        REQUIRE(expected_deg == degree);
        REQUIRE(expected_rad == Approx(radian));
    }
}