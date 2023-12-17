#include "../../include/Entities/Box.hpp"

void Box::update()
{
    //...
}

void Box::render(sf::RenderTarget *target)
{
    target->draw(this->box);
}