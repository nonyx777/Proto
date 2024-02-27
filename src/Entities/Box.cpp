#include "../../include/Entities/Box.hpp"

Box::Box()
{
    this->initVariables();
}

Box::Box(uint size)
{
    this->property.setSize(sf::Vector2f(size, size));
    this->property.setOrigin(this->property.getSize() / 2.f);
    this->property.setFillColor(sf::Color::White);
}

Box::Box(uint size, sf::Vector2f position)
{
    this->property.setSize(sf::Vector2f(size, size));
    this->property.setPosition(position);
    this->property.setFillColor(sf::Color::Transparent);
    this->property.setOutlineColor(sf::Color::White);
    this->property.setOutlineThickness(0.5f);
}

void Box::initVariables()
{
    this->inverseMass = this->mass == 0.f ? 100000.f : 1.f / this->mass;
    this->property.setSize(sf::Vector2f(10.f, 10.f));
    this->property.setFillColor(sf::Color::White);
    this->property.setOrigin(this->property.getSize() / 2.f);
}

void Box::calcMomentOfInertia()
{
    //m(h^2 + w^2) / 12
    sf::FloatRect bounds = this->property.getGlobalBounds();
    this->momentOfInertia = this->mass * ((bounds.height * bounds.height) + (bounds.width * bounds.width)) / 12.f;
}

void Box::update()
{
    euler(&this->property);
}

void Box::render(sf::RenderTarget *target)
{
    target->draw(this->property);
}