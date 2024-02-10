#include "../../include/Util/Collision.hpp"

// defining functions
// intersection check
bool Collision::_boxOverlapping(float min_a, float max_a, float min_b, float max_b)
{
    return min_b <= max_a && min_a <= max_b;
}
bool Collision::_circleOverlapping(float radius_a, float radius_b, sf::Vector2f origin_a, sf::Vector2f origin_b)
{
    return Math::_length(origin_b - origin_a) <= (radius_a + radius_b);
}
bool Collision::_circleSegmentOverlapping(Circle &a, Line &l)
{
    if (this->_circlePointCollide(a, l.base))
    {
        nearest_point = l.base;
        return this->_circlePointCollide(a, nearest_point);
    }
    if (this->_circlePointCollide(a, l.direction))
    {
        nearest_point = l.direction;
        return this->_circlePointCollide(a, nearest_point);
    }

    sf::Vector2f d = l.direction - l.base;
    sf::Vector2f lc = a.property.getPosition() - l.base;
    sf::Vector2f p = Math::_project(lc, d);
    nearest_point = l.base + p;

    return this->_circlePointCollide(a, nearest_point) &&
           Math::_length(p) <= Math::_length(d) &&
           0 <= Math::_dot(p, d);
}
// actual collision functions
bool Collision::_linesCollide(Line &a, Line &b)
{
    if (Math::_parallel(a.direction, b.direction))
        return false;
    else
        return true;
}

bool Collision::_boxCollide(Box &a, Box &b)
{
    sf::FloatRect a_bound = a.property.getGlobalBounds();
    sf::FloatRect b_bound = b.property.getGlobalBounds();
    float a_left = a_bound.left;
    float a_right = a_bound.left + a_bound.width;
    float b_left = b_bound.left;
    float b_right = b_bound.left + b_bound.width;

    float a_bottom = a_bound.top + a_bound.height;
    float a_top = a_bound.top;
    float b_bottom = b_bound.top + b_bound.height;
    float b_top = b_bound.top;

    return this->_boxOverlapping(a_left, a_right, b_left, b_right) && this->_boxOverlapping(a_top, a_bottom, b_top, b_bottom);
}

bool Collision::_circleCollide(Circle &a, Circle &b)
{
    return _circleOverlapping(a.property.getRadius(), b.property.getRadius(), a.property.getPosition(), b.property.getPosition());
}
bool Collision::_circlePointCollide(Circle &a, sf::Vector2f point)
{
    sf::Vector2f displacement = Math::_displacement(a.property.getPosition(), point);
    float distance = Math::_length(displacement);
    return distance <= a.property.getRadius();
}
bool Collision::_circleWindowCollide(Circle &a, Line l1, Line l2, Line l3, Line l4)
{
    return this->_circleSegmentOverlapping(a, l1) || this->_circleSegmentOverlapping(a, l2) || this->_circleSegmentOverlapping(a, l3) || this->_circleSegmentOverlapping(a, l4);
}
bool Collision::_circleBoxCollide(Circle &circle, Box &box)
{
    sf::Vector2f clamped = this->clampOnRectangle(circle.property.getPosition(), box);
    tempo_position = clamped;
    return this->_circlePointCollide(circle, clamped);
}
// penetration and collision resolution
// circle-circle penetration resoultion
void Collision::_circlePenetrationResolution(Circle &a, Circle &b)
{
    sf::Vector2f normal = Math::_displacement(a.property.getPosition(), b.property.getPosition());
    float distance = Math::_length(normal);
    float penetration_depth = (a.property.getRadius() + b.property.getRadius()) - distance;
    sf::Vector2f penetration_resolution_vector = Math::_normalize(normal) * penetration_depth / (a.inverseMass + b.inverseMass);
    this->a_position = penetration_resolution_vector * a.inverseMass;
    this->b_position = -penetration_resolution_vector * b.inverseMass;
}
void Collision::_circleCollisionResolution(Circle &a, Circle &b)
{
    sf::Vector2f normal = Math::_displacement(a.property.getPosition(), b.property.getPosition());
    normal = Math::_normalize(normal);
    sf::Vector2f relative_velocity = Math::_displacement(a.velocity, b.velocity);
    float separating_velocity = Math::_dot(relative_velocity, normal);
    float impulse = -separating_velocity - separating_velocity / (a.inverseMass + b.inverseMass);
    sf::Vector2f impulse_vector = normal * impulse;
    this->a_velocity = impulse_vector * a.inverseMass * a.elasticity;
    this->b_velocity = -impulse_vector * b.inverseMass * b.elasticity;
}
// circle-point penetration resolution
void Collision::_circlePointPenetrationResolution(Circle &a, sf::Vector2f &p)
{
    sf::Vector2f normal = Math::_displacement(a.property.getPosition(), p);
    float distance = Math::_length(normal);
    float penetration_distance = a.property.getRadius() - distance;
    sf::Vector2f penetration_resolution_vector = Math::_normalize(normal) * penetration_distance / 2.f;
    this->a_position = penetration_resolution_vector;
}
void Collision::_circlePointCollisionResolution(Circle &circle, sf::Vector2f &point)
{
    sf::Vector2f normal = Math::_displacement(circle.property.getPosition(), point);
    normal = Math::_normalize(normal);
    sf::Vector2f relative_velocity = Math::_displacement(circle.velocity, sf::Vector2f(0.f, 0.f));
    float separating_velocity = Math::_dot(relative_velocity, normal);
    sf::Vector2f separating_velocity_vector = normal * separating_velocity;
    this->b_velocity = -separating_velocity_vector * circle.elasticity;
}
bool Collision::_orientedBoxCollide(Box &a, Box &b)
{
    // get bounds of both of the boxes
    // box a
    sf::FloatRect a_bounds = a.property.getGlobalBounds();
    std::vector<sf::Vector2f> a_edges;
    a_edges.push_back(sf::Vector2f(a_bounds.left, a_bounds.top));                                    // top left
    a_edges.push_back(sf::Vector2f(a_bounds.left + a_bounds.width, a_bounds.top));                   // top right
    a_edges.push_back(sf::Vector2f(a_bounds.left, a_bounds.top + a_bounds.height));                  // bottom left
    a_edges.push_back(sf::Vector2f(a_bounds.left + a_bounds.width, a_bounds.top + a_bounds.height)); // bottom right
    // box b
    sf::FloatRect b_bounds = b.property.getGlobalBounds();
    std::vector<sf::Vector2f> b_edges;
    b_edges.push_back(sf::Vector2f(b_bounds.left, b_bounds.top));                                    // top left
    b_edges.push_back(sf::Vector2f(b_bounds.left + b_bounds.width, b_bounds.top));                   // top right
    b_edges.push_back(sf::Vector2f(b_bounds.left, b_bounds.top + b_bounds.height));                  // bottom left
    b_edges.push_back(sf::Vector2f(b_bounds.left + b_bounds.width, b_bounds.top + b_bounds.height)); // bottom right

    // get axes
    sf::Vector2f tempo_axis;
    // a axis
    std::vector<sf::Vector2f> a_axis;
    tempo_axis = Math::_normalize(a_edges[0] - a_edges[2]);
    a_axis.push_back(tempo_axis);
    tempo_axis = Math::_normalize(a_edges[2] - a_edges[3]);
    a_axis.push_back(tempo_axis);

    // b axis
    std::vector<sf::Vector2f> b_axis;
    tempo_axis = Math::_normalize(b_edges[0] - b_edges[2]);
    b_axis.push_back(tempo_axis);
    tempo_axis = Math::_normalize(b_edges[2] - b_edges[3]);
    b_axis.push_back(tempo_axis);

    // project edges of the boxes into a and b axis
    std::vector<sf::Vector2f> a_projected_edges;
    std::vector<sf::Vector2f> b_projected_edges;
    for (sf::Vector2f axis : a_axis)
    {
        for (sf::Vector2f edge : a_edges)
        {
            sf::Vector2f projected = Math::_project(edge, axis);
            a_projected_edges.push_back(projected);
        }
        for (sf::Vector2f edge : b_edges)
        {
            sf::Vector2f projected = Math::_project(edge, axis);
            b_projected_edges.push_back(projected);
        }
        // get minimum and maximum from the projected edges
        sf::Vector2f a_min_edge = Math::_minVector(a_projected_edges);
        sf::Vector2f a_max_edge = Math::_maxVector(a_projected_edges);

        sf::Vector2f b_min_edge = Math::_minVector(b_projected_edges);
        sf::Vector2f b_max_edge = Math::_maxVector(b_projected_edges);
        // check if is there is any absence of intersection
        // return false if there exists even one occurence that intersection did not exist
        if ((this->_boxOverlapping(a_min_edge.x, a_max_edge.x, b_min_edge.x, b_max_edge.x) &&
             this->_boxOverlapping(a_min_edge.y, a_max_edge.y, b_min_edge.y, b_min_edge.y)) == false)
        {
            return false;
        }
        a_projected_edges.clear();
        b_projected_edges.clear();
    }
    for (sf::Vector2f axis : b_axis)
    {
        for (sf::Vector2f edge : a_edges)
        {
            sf::Vector2f projected = Math::_project(edge, axis);
            a_projected_edges.push_back(projected);
        }
        for (sf::Vector2f edge : b_edges)
        {
            sf::Vector2f projected = Math::_project(edge, axis);
            b_projected_edges.push_back(projected);
        }
        // get minimum and maximum from the projected edges
        sf::Vector2f a_min_edge = Math::_minVector(a_projected_edges);
        sf::Vector2f a_max_edge = Math::_maxVector(a_projected_edges);

        sf::Vector2f b_min_edge = Math::_minVector(b_projected_edges);
        sf::Vector2f b_max_edge = Math::_maxVector(b_projected_edges);
        // check if is there is any absence of intersection
        // return false if there exists even one occurence that intersection did not exist
        if ((this->_boxOverlapping(a_min_edge.x, a_max_edge.x, b_min_edge.x, b_max_edge.x) &&
             this->_boxOverlapping(a_min_edge.y, a_max_edge.y, b_min_edge.y, b_min_edge.y)) == false)
        {
            return false;
        }
        a_projected_edges.clear();
        b_projected_edges.clear();
    }

    return true;
}

// box-box penetration resoultion
void Collision::_boxPenetrationResolution(Box &a, Box &b)
{
    sf::Vector2f normal = a.property.getPosition() - b.property.getPosition();
    float distance = Math::_length(normal);
    float a_x_half = a.property.getSize().x / 2.f;
    float b_x_half = b.property.getSize().x / 2.f;
    float overlap_x = normal.x - (a_x_half + b_x_half);
    float overlap_y = normal.y - (a_x_half + b_x_half);
    float penetration_depth = min(overlap_x, overlap_y);
    sf::Vector2f penetration_resolution_vector = Math::_normalize(normal) * penetration_depth / (a_x_half + b_x_half);

    this->a_position = -penetration_resolution_vector;
    this->b_position = penetration_resolution_vector;
}
// box-box collision resolution
void Collision::_boxCollisionResolution(Box &a, Box &b)
{
    sf::Vector2f normal = a.property.getPosition() - b.property.getPosition();
    normal = Math::_normalize(normal);
    sf::Vector2f relative_velocity = a.velocity - b.velocity;
    float separating_velocity = Math::_dot(relative_velocity, normal);
    sf::Vector2f separating_velocity_vector = normal * separating_velocity;
    this->a_velocity = -separating_velocity_vector;
    this->b_velocity = separating_velocity_vector;
}
// circle-box penetration resolution
void Collision::_circleBoxPenetrationResolution(Circle &circle, Box &box)
{
    sf::Vector2f normal = circle.property.getPosition() - box.property.getPosition();
    normal = Math::_normalize(normal);
    sf::Vector2f nearest_position = this->clampOnRectangle(circle.property.getPosition(), box);
    float distance = Math::_length(circle.property.getPosition() - nearest_position);
    float penetration_depth = circle.property.getRadius() - distance;
    sf::Vector2f penetration_resolution_vector = normal * penetration_depth;
    this->a_position = penetration_resolution_vector;
    this->b_position = -penetration_resolution_vector;
}

//...
sf::Vector2f Collision::clampOnRectangle(sf::Vector2f point, Box box)
{
    sf::Vector2f clamp;
    clamp.x = Math::_clampOnRange(point.x, box.property.getGlobalBounds().left, box.property.getGlobalBounds().left + box.property.getGlobalBounds().width);
    clamp.y = Math::_clampOnRange(point.y, box.property.getGlobalBounds().top, box.property.getGlobalBounds().top + box.property.getGlobalBounds().height);
    return clamp;
}