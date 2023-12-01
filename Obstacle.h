#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "Collision.h"
using namespace Collision;
#pragma once
class Obstacle
{
	sf::Vector2f pos;
public:
	sf::RectangleShape wall;
	void InitWall(sf::Color color, sf::Vector2f pos, sf::Vector2f size);
	void DrawWall(sf::RenderWindow& window);
};

