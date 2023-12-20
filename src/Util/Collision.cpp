#include "../../include/Util/Collision.hpp"

//defining functions
    //intersection check
bool Collision::_boxOverlapping(float min_a, float max_a, float min_b, float max_b){
    return min_b <= max_a && min_a <= max_b;
}
bool Collision::_ballOverlapping(float radius_a, float radius_b, sf::Vector2f origin_a, sf::Vector2f origin_b){
    return math._length(origin_b - origin_a) <= (radius_a + radius_b);
}
bool Collision::_ballSegmentOverlapping(Circle &a, Line &l){
    if(this->_ballPointCollide(a, l.base)){
        nearest_point = l.base;
        return this->_ballPointCollide(a, nearest_point);
    }
    if(this->_ballPointCollide(a, l.direction)){
        nearest_point = l.direction;
        return this->_ballPointCollide(a, nearest_point);
    }

    sf::Vector2f d = l.direction - l.base;
    sf::Vector2f lc = a.circle.getPosition() - l.base;
    sf::Vector2f p = this->math._project(lc, d);
    nearest_point = l.base + p;

    return this->_ballPointCollide(a, nearest_point) && 
    this->math._length(p) <= this->math._length(d) && 
    0 <= this->math._dot(p, d);
}
//penetration and collision resolution
    //ball-ball penetration resoultion
void Collision::_ballPenetrationResolution(Circle &a, Circle &b){
    sf::Vector2f normal = this->math._displacement(a.circle.getPosition(), b.circle.getPosition());
    float distance = this->math._length(normal);
    float penetration_depth = (a.circle.getRadius() + b.circle.getRadius()) - distance;
    sf::Vector2f penetration_resolution_vector = this->math._normalize(normal) * penetration_depth/(a.inverseMass + b.inverseMass);
    this->a_position = penetration_resolution_vector * a.inverseMass;
    this->b_position = -penetration_resolution_vector * b.inverseMass;
}
void Collision::_ballCollisionResolution(Circle &a, Circle &b){
    sf::Vector2f normal = this->math._displacement(a.circle.getPosition(), b.circle.getPosition());
    normal = this->math._normalize(normal);
    sf::Vector2f relative_velocity = this->math._displacement(a.velocity, b.velocity);
    float separating_velocity = this->math._dot(relative_velocity, normal);
    float impulse = -separating_velocity - separating_velocity/(a.inverseMass + b.inverseMass);
    sf::Vector2f impulse_vector = normal * impulse;
    this->a_velocity = impulse_vector * a.inverseMass * a.elasticity;
    this->b_velocity = -impulse_vector * b.inverseMass * b.elasticity;
}
    //ball-point penetration resolution
void Collision::_ballPointPenetrationResolution(Circle &a, sf::Vector2f &p){
    sf::Vector2f normal = this->math._displacement(a.circle.getPosition(), p);
    float distance = this->math._length(normal);
    float penetration_distance = a.circle.getRadius() - distance;
    sf::Vector2f penetration_resolution_vector = this->math._normalize(normal) * penetration_distance/2.f;
    this->a_position = penetration_resolution_vector;
}
void Collision::_ballPointCollisionResolution(Circle &ball, sf::Vector2f &point){
    sf::Vector2f normal = this->math._displacement(ball.circle.getPosition(), point);
    normal = this->math._normalize(normal);
    sf::Vector2f relative_velocity = this->math._displacement(ball.velocity, sf::Vector2f(0.f, 0.f));
    float separating_velocity = this->math._dot(relative_velocity, normal);
    sf::Vector2f separating_velocity_vector = normal * separating_velocity;
    this->b_velocity = -separating_velocity_vector * ball.elasticity;
}

    //box-box penetration resoultion
// void Collision::_boxBoxPenetrationResolution(Box &a, Box &b){
//     sf::Vector2f normal = a.getBoxPosition() - b.getBoxPosition();
//     float distance = this->math._length(normal);
//     float a_x_half = a.box_property.getSize().x/2.f;
//     float b_x_half = b.box_property.getSize().x/2.f;
//     float overlap_x = normal.x - (a_x_half + b_x_half);
//     float overlap_y = normal.y - (a_x_half + b_x_half);
//     float penetration_depth = min(overlap_x, overlap_y);
//     sf::Vector2f penetration_resolution_vector = this->math._normalize(normal) * penetration_depth/(a_x_half + b_x_half);

//     this->a_position = -penetration_resolution_vector;
//     this->b_position = penetration_resolution_vector;
// }
    //box-box collision resolution
// void Collision::_boxBoxCollisionResolution(Box &a, Box &b){
//     sf::Vector2f normal = a.getBoxPosition() - b.getBoxPosition();
//     normal = this->math._normalize(normal);
//     sf::Vector2f relative_velocity = a.getBoxVelocity() - b.getBoxVelocity();
//     float separating_velocity = this->math._dot(relative_velocity, normal);
//     sf::Vector2f separating_velocity_vector = normal * separating_velocity;
//     this->a_velocity = -separating_velocity_vector;
//     this->b_velocity = separating_velocity_vector;
// }
    //ball-box penetration resolution
// void Collision::_ballBoxPenetrationResolution(Circle &ball, Box &box){
//     sf::Vector2f normal = ball.getBallPosition() - box.getBoxPosition();
//     normal = this->math._normalize(normal);
//     sf::Vector2f nearest_position = this->clampOnRectangle(ball.getBallPosition(), box);
//     float distance = this->math._length(ball.getBallPosition() - nearest_position);
//     float penetration_depth = ball.getBallRadius() - distance;
//     sf::Vector2f penetration_resolution_vector = normal * penetration_depth;
//     this->a_position = penetration_resolution_vector;
//     this->b_position = -penetration_resolution_vector;
// }

    //ball-box collision resolution

    //actual collision functions
// bool Collision::_linesCollide(Line &a, Line &b){
//     if(math._parallelVectors(a.direction, b.direction))
//         return false;
//     else 
//         return true;
// }

// bool Collision::_boxCollide(Box &a, Box &b){
//     sf::FloatRect a_bound = a.box_property.getGlobalBounds();
//     sf::FloatRect b_bound = b.box_property.getGlobalBounds();
//     float a_left = a_bound.left;
//     float a_right = a_bound.left + a_bound.width;
//     float b_left = b_bound.left;
//     float b_right = b_bound.left + b_bound.width;

//     float a_bottom = a_bound.top + a_bound.height;
//     float a_top = a_bound.top;
//     float b_bottom = b_bound.top + b_bound.height;
//     float b_top = b_bound.top;

//     return this->_boxOverlapping(a_left, a_right, b_left, b_right) && this->_boxOverlapping(a_top, a_bottom, b_top, b_bottom);
// }

bool Collision::_ballCollide(Circle &a, Circle &b){
    return _ballOverlapping(a.circle.getRadius(), b.circle.getRadius(), a.circle.getPosition(), b.circle.getPosition());
}
bool Collision::_ballPointCollide(Circle &a, sf::Vector2f point){
    sf::Vector2f displacement = this->math._displacement(a.circle.getPosition(), point);
    float distance = this->math._length(displacement);
    return distance <= a.circle.getRadius();
}
// bool Collision::_ballWindowCollide(sf::CircleShape &a, Line l1, Line l2, Line l3, Line l4){
//     return this->_ballLineOverlapping(a, l1) || this->_ballLineOverlapping(a, l2) || this->_ballLineOverlapping(a, l3) || this->_ballLineOverlapping(a, l4);
// }
// bool Collision::_ballBoxCollide(Circle &ball, Box &box){
//     sf::Vector2f clamped = this->clampOnRectangle(ball.getBallPosition(), box);
//     tempo_position = clamped;
//     return this->_ballPointCollide(ball.ball_property, clamped);
// }

//...
// sf::Vector2f Collision::clampOnRectangle(sf::Vector2f point, Box box){
//     sf::Vector2f clamp;
//     clamp.x = this->math._clampOnRange(point.x, box.box_property.getGlobalBounds().left, box.box_property.getGlobalBounds().left + box.box_property.getGlobalBounds().width);
//     clamp.y = this->math._clampOnRange(point.y, box.box_property.getGlobalBounds().top, box.box_property.getGlobalBounds().top + box.box_property.getGlobalBounds().height);
//     return clamp;
// }