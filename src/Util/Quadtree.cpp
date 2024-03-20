#include "../../include/Util/Quadtree.hpp"

Quad::Quad()
{
    topLeft = sf::Vector2f(0, 0);
    botRight = sf::Vector2f(0, 0);
    capacity = 4;

    Circle *node = NULL;
    Quad *ne = NULL;
    Quad *nw = NULL;
    Quad *sw = NULL;
    Quad *se = NULL;
}

Quad::Quad(sf::Vector2f topLeft_, sf::Vector2f botRight_)
{
    topLeft = topLeft_;
    botRight = botRight_;
    capacity = 4;
    sf::Vector2f size = sf::Vector2f(botRight.x - topLeft.x, botRight.y - topLeft.y);
    sf::Vector2f position = sf::Vector2f((topLeft.x + botRight.x) / 2.f, (topLeft.y + botRight.y) / 2.f);

    box = Box(size, position);

    Circle *node = NULL;
    Quad *ne = NULL;
    Quad *nw = NULL;
    Quad *sw = NULL;
    Quad *se = NULL;
}

void Quad::insert(Circle *node)
{
    if (node == NULL)
        return;

    if (!collision._boxPointCollide(this->box, node->property.getPosition()))
        return;

    if (nodes.size() < capacity && nw == NULL)
    {
        nodes.push_back(node);
        return;
    }

    if (nw == NULL)
    {
        sf::Vector2f mid = sf::Vector2f((topLeft.x + botRight.x) / 2, (topLeft.y + botRight.y) / 2);
        nw = new Quad(topLeft, mid);
        sw = new Quad(sf::Vector2f(topLeft.x, mid.y), sf::Vector2f(mid.x, botRight.y));
        ne = new Quad(sf::Vector2f(mid.x, topLeft.y), sf::Vector2f(botRight.x, mid.y));
        se = new Quad(mid, botRight);
    }

    if (node->property.getPosition().x < (topLeft.x + botRight.x) / 2)
    {
        if (node->property.getPosition().y < (topLeft.y + botRight.y) / 2)
            nw->insert(node); // North-West
        else
            sw->insert(node); // South-West
    }
    else
    {
        if (node->property.getPosition().y < (topLeft.y + botRight.y) / 2)
            ne->insert(node); // North-East
        else
            se->insert(node); // South-East
    }
}

std::vector<Circle *> Quad::search(Box range)
{
    std::vector<Circle *> found;

    if (!collision._boxCollide(this->box, range))
    {
        return found;
    }

    for (int i = 0; i < nodes.size(); i++)
    {
        if (collision._boxPointCollide(range, nodes[i]->property.getPosition()))
            found.push_back(nodes[i]);
    }

    if (nw == NULL)
    {

        return found;
    }

    if (nw != NULL)
    {
        std::vector<Circle *> result = nw->search(range);
        found.insert(found.end(), result.begin(), result.end());
    }

    if (sw != NULL)
    {
        std::vector<Circle *> result = sw->search(range);
        found.insert(found.end(), result.begin(), result.end());
    }

    if (ne != NULL)
    {
        std::vector<Circle *> result = ne->search(range);
        found.insert(found.end(), result.begin(), result.end());
    }

    if (se != NULL)
    {
        std::vector<Circle *> result = se->search(range);
        found.insert(found.end(), result.begin(), result.end());
    }

    return found;
}

void Quad::clear()
{
    if(nw == NULL){
        nodes.clear();
        return;
    }

    nw->clear();
    sw->clear();
    ne->clear();
    se->clear();

    nodes.clear();

    delete nw;
    delete sw;
    delete ne;
    delete se;

    nw = NULL;
    sw = NULL;
    ne = NULL;
    se = NULL;
}