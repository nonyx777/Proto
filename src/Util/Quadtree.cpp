#include "../../include/Util/Quadtree.hpp"

Quad::Quad()
{
    topLeft = sf::Vector2f(0, 0);
    botRight = sf::Vector2f(0, 0);
    capacity = 4;

    Node *node = NULL;
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
    sf::Vector2f size = sf::Vector2f((float)botRight.x - (float)topLeft.x, (float)botRight.y - (float)topLeft.y);
    sf::Vector2f position = sf::Vector2f(((float)topLeft.x + (float)botRight.x) / 2.f, ((float)topLeft.y + (float)botRight.y) / 2.f);

    box = Box(size, position);

    Node *node = NULL;
    Quad *ne = NULL;
    Quad *nw = NULL;
    Quad *sw = NULL;
    Quad *se = NULL;
}

void Quad::insert(Node *node)
{
    if (node == NULL)
        return;

    if (!collision._boxPointCollide(this->box, node->pos))
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

    if (node->pos.x < (topLeft.x + botRight.x) / 2)
    {
        if (node->pos.y < (topLeft.y + botRight.y) / 2)
            nw->insert(node); // North-West
        else
            sw->insert(node); // South-West
    }
    else
    {
        if (node->pos.y < (topLeft.y + botRight.y) / 2)
            ne->insert(node); // North-East
        else
            se->insert(node); // South-East
    }
}

// Find a node in a quadtree
std::vector<Node *> Quad::search(Box range)
{
    std::vector<Node *> found;

    if (!collision._boxCollide(this->box, range))
    {
        return found;
    }

    for (int i = 0; i < nodes.size(); i++)
    {
        if (collision._boxPointCollide(range, nodes[i]->pos))
            found.push_back(nodes[i]);
    }

    if (nw == NULL)
    {

        return found;
    }

    if (nw != NULL)
    {
        std::vector<Node *> result = nw->search(range);
        found.insert(found.end(), result.begin(), result.end());
    }

    if (sw != NULL)
    {
        std::vector<Node *> result = sw->search(range);
        found.insert(found.end(), result.begin(), result.end());
    }

    if (ne != NULL)
    {
        std::vector<Node *> result = ne->search(range);
        found.insert(found.end(), result.begin(), result.end());
    }

    if (se != NULL)
    {
        std::vector<Node *> result = se->search(range);
        found.insert(found.end(), result.begin(), result.end());
    }

    return found;
}