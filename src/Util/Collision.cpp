#include "../../include/Util/Collision.hpp"

//defining functions
    //intersection check
bool Collision::_boxOverlapping(float min_a, float max_a, float min_b, float max_b){
    return min_b <= max_a && min_a <= max_b;
}
bool Collision::_circleOverlapping(float radius_a, float radius_b, sf::Vector2f origin_a, sf::Vector2f origin_b){
    return Math::_length(origin_b - origin_a) <= (radius_a + radius_b);
}
bool Collision::_circleSegmentOverlapping(Circle &a, Line &l){
    if(this->_circlePointCollide(a, l.base)){
        nearest_point = l.base;
        return this->_circlePointCollide(a, nearest_point);
    }
    if(this->_circlePointCollide(a, l.direction)){
        nearest_point = l.direction;
        return this->_circlePointCollide(a, nearest_point);
    }

    sf::Vector2f d = l.direction - l.base;
    sf::Vector2f lc = a.circle.getPosition() - l.base;
    sf::Vector2f p = Math::_project(lc, d);
    nearest_point = l.base + p;

    return this->_circlePointCollide(a, nearest_point) && 
    Math::_length(p) <= Math::_length(d) && 
    0 <= Math::_dot(p, d);
}
//penetration and collision resolution
    //circle-circle penetration resoultion
void Collision::_circlePenetrationResolution(Circle &a, Circle &b){
    sf::Vector2f normal = Math::_displacement(a.circle.getPosition(), b.circle.getPosition());
    float distance = Math::_length(normal);
    float penetration_depth = (a.circle.getRadius() + b.circle.getRadius()) - distance;
    sf::Vector2f penetration_resolution_vector = Math::_normalize(normal) * penetration_depth/(a.inverseMass + b.inverseMass);
    this->a_position = penetration_resolution_vector * a.inverseMass;
    this->b_position = -penetration_resolution_vector * b.inverseMass;
}
void Collision::_circleCollisionResolution(Circle &a, Circle &b){
    sf::Vector2f normal = Math::_displacement(a.circle.getPosition(), b.circle.getPosition());
    normal = Math::_normalize(normal);
    sf::Vector2f relative_velocity = Math::_displacement(a.velocity, b.velocity);
    float separating_velocity = Math::_dot(relative_velocity, normal);
    float impulse = -separating_velocity - separating_velocity/(a.inverseMass + b.inverseMass);
    sf::Vector2f impulse_vector = normal * impulse;
    this->a_velocity = impulse_vector * a.inverseMass * a.elasticity;
    this->b_velocity = -impulse_vector * b.inverseMass * b.elasticity;
}
    //circle-point penetration resolution
void Collision::_circlePointPenetrationResolution(Circle &a, sf::Vector2f &p){
    sf::Vector2f normal = Math::_displacement(a.circle.getPosition(), p);
    float distance = Math::_length(normal);
    float penetration_distance = a.circle.getRadius() - distance;
    sf::Vector2f penetration_resolution_vector = Math::_normalize(normal) * penetration_distance/2.f;
    this->a_position = penetration_resolution_vector;
}
void Collision::_circlePointCollisionResolution(Circle &circle, sf::Vector2f &point){
    sf::Vector2f normal = Math::_displacement(circle.circle.getPosition(), point);
    normal = Math::_normalize(normal);
    sf::Vector2f relative_velocity = Math::_displacement(circle.velocity, sf::Vector2f(0.f, 0.f));
    float separating_velocity = Math::_dot(relative_velocity, normal);
    sf::Vector2f separating_velocity_vector = normal * separating_velocity;
    this->b_velocity = -separating_velocity_vector * circle.elasticity;
}

    //box-box penetration resoultion
void Collision::_boxPenetrationResolution(Box &a, Box &b){
    sf::Vector2f normal = a.box.getPosition() - b.box.getPosition();
    float distance = Math::_length(normal);
    float a_x_half = a.box.getSize().x/2.f;
    float b_x_half = b.box.getSize().x/2.f;
    float overlap_x = normal.x - (a_x_half + b_x_half);
    float overlap_y = normal.y - (a_x_half + b_x_half);
    float penetration_depth = min(overlap_x, overlap_y);
    sf::Vector2f penetration_resolution_vector = Math::_normalize(normal) * penetration_depth/(a_x_half + b_x_half);

    this->a_position = -penetration_resolution_vector;
    this->b_position = penetration_resolution_vector;
}
    //box-box collision resolution
void Collision::_boxCollisionResolution(Box &a, Box &b){
    sf::Vector2f normal = a.box.getPosition() - b.box.getPosition();
    normal = Math::_normalize(normal);
    sf::Vector2f relative_velocity = a.velocity - b.velocity;
    float separating_velocity = Math::_dot(relative_velocity, normal);
    sf::Vector2f separating_velocity_vector = normal * separating_velocity;
    this->a_velocity = -separating_velocity_vector;
    this->b_velocity = separating_velocity_vector;
}
    //circle-box penetration resolution
void Collision::_circleBoxPenetrationResolution(Circle &circle, Box &box){
    sf::Vector2f normal = circle.circle.getPosition() - box.box.getPosition();
    normal = Math::_normalize(normal);
    sf::Vector2f nearest_position = this->clampOnRectangle(circle.circle.getPosition(), box);
    float distance = Math::_length(circle.circle.getPosition() - nearest_position);
    float penetration_depth = circle.circle.getRadius() - distance;
    sf::Vector2f penetration_resolution_vector = normal * penetration_depth;
    this->a_position = penetration_resolution_vector;
    this->b_position = -penetration_resolution_vector;
}

    //circle-box collision resolution

    //actual collision functions
bool Collision::_linesCollide(Line &a, Line &b){
    if(Math::_parallel(a.direction, b.direction))
        return false;
    else 
        return true;
}

bool Collision::_boxCollide(Box &a, Box &b){
    sf::FloatRect a_bound = a.box.getGlobalBounds();
    sf::FloatRect b_bound = b.box.getGlobalBounds();
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

bool Collision::_circleCollide(Circle &a, Circle &b){
    return _circleOverlapping(a.circle.getRadius(), b.circle.getRadius(), a.circle.getPosition(), b.circle.getPosition());
}
bool Collision::_circlePointCollide(Circle &a, sf::Vector2f point){
    sf::Vector2f displacement = Math::_displacement(a.circle.getPosition(), point);
    float distance = Math::_length(displacement);
    return distance <= a.circle.getRadius();
}
bool Collision::_circleWindowCollide(Circle &a, Line l1, Line l2, Line l3, Line l4){
    return this->_circleSegmentOverlapping(a, l1) || this->_circleSegmentOverlapping(a, l2) || this->_circleSegmentOverlapping(a, l3) || this->_circleSegmentOverlapping(a, l4);
}
bool Collision::_circleBoxCollide(Circle &circle, Box &box){
    sf::Vector2f clamped = this->clampOnRectangle(circle.circle.getPosition(), box);
    tempo_position = clamped;
    return this->_circlePointCollide(circle, clamped);
}

//...
sf::Vector2f Collision::clampOnRectangle(sf::Vector2f point, Box box){
    sf::Vector2f clamp;
    clamp.x = Math::_clampOnRange(point.x, box.box.getGlobalBounds().left, box.box.getGlobalBounds().left + box.box.getGlobalBounds().width);
    clamp.y = Math::_clampOnRange(point.y, box.box.getGlobalBounds().top, box.box.getGlobalBounds().top + box.box.getGlobalBounds().height);
    return clamp;
}