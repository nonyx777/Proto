#include <iostream>
#include <SFML/Graphics.hpp>
#include "Math.hpp"
#include "../Entities/Entities.hpp"

using namespace std;

class Collision
{
private:
    // instantiating objects
    Math math;
    Circle circle;
    Line line;
    Box box;

public:
    // storing vital positions
    sf::Vector2f a_position;
    sf::Vector2f b_position;
    sf::Vector2f nearest_point;
    sf::Vector2f a_velocity;
    sf::Vector2f b_velocity;
    sf::Vector2f tempo_position;
    // intersection check
    bool _boxOverlapping(float min_a, float max_a, float min_b, float max_b);
    bool _ballOverlapping(float radius_a, float radius_b, sf::Vector2f origin_a, sf::Vector2f origin_b);
    // bool _boxLineOverlapping();
    bool _ballSegmentOverlapping(Circle &a, Line &l);
    // penetretion and collision resolution
    void _ballPenetrationResolution(Circle &a, Circle &b);
    void _ballCollisionResolution(Circle &a, Circle &b);
    void _ballPointPenetrationResolution(Circle &circle, sf::Vector2f &p);
    void _ballPointCollisionResolution(Circle &circle, sf::Vector2f &point);
    // void _boxBoxPenetrationResolution(Box &a, Box &b);
    // void _boxBoxCollisionResolution(Box &a, Box &b);
    // void _ballBoxPenetrationResolution(Circle &circle, Box &box);
    // void _ballBoxCollisionResolution(Circle &circle, Box &box);

    // actual collision function
    //  bool _linesCollide(Line &a, Line &b);
    //  bool _boxCollide(Box &a, Box &b);
    bool _ballCollide(Circle &a, Circle &b);
    // bool _boxLineCollide();
    bool _ballPointCollide(Circle &a, sf::Vector2f point);
    // bool _ballWindowCollide(sf::CircleShape &a, Line l1, Line l2, Line l3, Line l4);
    // bool _ballBoxCollide(Circle &circle, Box &box);
    //...
    // sf::Vector2f clampOnRectangle(sf::Vector2f point, Box box);
};