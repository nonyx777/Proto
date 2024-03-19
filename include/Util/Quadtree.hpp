#pragma once
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "../GameObject.hpp"
#include "../Entities/Entities.hpp"
#include "Collision.hpp"

// Used to hold details of a point
struct Point
{
	int x;
	int y;
	Point(float _x, float _y)
	{
		x = _x;
		y = _y;
	}
	Point()
	{
		x = 0;
		y = 0;
	}
};

// The objects that we want stored in the quadtree
struct Node
{
	sf::Vector2f pos;
	int data;
	Node(sf::Vector2f _pos, int _data)
	{
		pos = _pos;
		data = _data;
	}
	Node() { data = 0; }
};

class Quad
{
public:
    sf::Vector2f topLeft;
    sf::Vector2f botRight;
    Node *node;
    std::vector<Node*> nodes;
    int capacity;

    Box box;

    Quad *ne;
    Quad *nw;
    Quad *sw;
    Quad *se;

    Quad();
    Quad(sf::Vector2f topLeft, sf::Vector2f botRight);
    Collision collision;

    void insert(Node *node);
    std::vector<Node*> search(Box range);
};